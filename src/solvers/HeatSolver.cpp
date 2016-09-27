#include "HeatSolver.hpp"

#include <deal.II/lac/dynamic_sparsity_pattern.h>

#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>

#include <deal.II/dofs/dof_tools.h>

#include <deal.II/fe/fe_values.h>

#include <deal.II/lac/solver.h>
#include <deal.II/lac/precondition.h>

#include <deal.II/numerics/error_estimator.h>
#include <deal.II/grid/grid_refinement.h>

#include <deal.II/numerics/data_out.h>
#include <fstream>

using namespace dealii;

HeatSolver::SimpleSolver::SimpleSolver(const MeshWrappers::SimpleShellMesh &mesh,
                                       const TaskReader::HeatProperties &heat_properties)
    :
    dof_handler(mesh.mesh()),
    rhs_function(&heat_properties.rhs_function),
    boundary_conditions({
                            std::make_pair<types::boundary_id,
                                           const SmartPointer<const Function<3>>>(0, &heat_properties.other_boundary_function),
                            std::make_pair<types::boundary_id,
                                           const SmartPointer<const Function<3>>>(2, &heat_properties.fairing_boundary_function)
                        }),
    fe(2),
    quadrature(2),
    a_square(heat_properties.a_square)
{

}

HeatSolver::SimpleSolver::~SimpleSolver()
{
    dof_handler.clear();
}

void HeatSolver::SimpleSolver::run(const boost::filesystem::path &output_dir)
{
    std::cout << "    Setup system..." << std::endl << std::flush;
    setup_system();
    std::cout << "    Number of degrees of freedom: " << dof_handler.n_dofs() << std::endl;

    std::cout << "    Assembling system..." << std::endl << std::flush;
    assemble_system();

    std::cout << "    Solving linear system..." << std::endl << std::flush;
    const size_t n_iter = solve_linear_system();
    std::cout << "    Solver converges in " << n_iter << " iterations." << std::endl;

    std::cout << "    Output solution..." << std::endl << std::flush;
    output_solution(output_dir);

}

void HeatSolver::SimpleSolver::setup_system()
{
    dof_handler.distribute_dofs(fe);

    solution.reinit(dof_handler.n_dofs());
    system_rhs.reinit(dof_handler.n_dofs());

    constraints.clear();
    DoFTools::make_hanging_node_constraints(dof_handler, constraints);
    boundary_conditions.interpolate_boundary_values(dof_handler, constraints);
    constraints.close();

    DynamicSparsityPattern dsp(dof_handler.n_dofs());
    DoFTools::make_sparsity_pattern(dof_handler, dsp, constraints, true);
    sparsity_pattern.copy_from(dsp);

    system_matrix.reinit(sparsity_pattern);
}

void HeatSolver::SimpleSolver::assemble_system()
{
    FEValues<3> fe_values(fe, quadrature,
                          update_values | update_gradients |
                          update_quadrature_points | update_JxW_values);

    const size_t dofs_per_cell = fe.dofs_per_cell;
    const size_t n_q_points = quadrature.size();

    FullMatrix<double> cell_matrix(dofs_per_cell, dofs_per_cell);
    Vector<double> cell_rhs(dofs_per_cell);

    std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);

    for (auto cell : dof_handler.active_cell_iterators())
    {
        fe_values.reinit(cell);

        cell_matrix = 0;
        cell_rhs = 0;

        for (size_t q = 0; q < n_q_points; ++q)
        {
            for (size_t i = 0; i < dofs_per_cell; ++i)
            {
                for (size_t j = 0; j < dofs_per_cell; ++j)
                {
                    cell_matrix(i, j) += fe_values.shape_grad(i, q) *
                                         fe_values.shape_grad(j, q) *
                                         fe_values.JxW(q) *
                                         a_square;
                }

                cell_rhs(i) += fe_values.shape_value(i, q) *
                               rhs_function->value(fe_values.quadrature_point(q)) *
                               fe_values.JxW(q);
            }
        }

        cell->get_dof_indices(local_dof_indices);

        constraints.distribute_local_to_global(cell_matrix,
                                               cell_rhs,
                                               local_dof_indices,
                                               system_matrix,
                                               system_rhs);

    }
}

size_t HeatSolver::SimpleSolver::solve_linear_system()
{
    SolverControl solver_control(dof_handler.n_dofs());
    SolverCG<> solver(solver_control);

    PreconditionSSOR<> preconditioner;
    preconditioner.initialize(system_matrix, 1.2);

    solver.solve(system_matrix, solution, system_rhs, preconditioner);

    constraints.distribute(solution);
    return solver_control.last_step();
}

void HeatSolver::SimpleSolver::output_solution(const boost::filesystem::path &output_dir)
{
    DataOut<3> data_out;

    data_out.attach_dof_handler(dof_handler);
    data_out.add_data_vector(solution, "T");

    data_out.build_patches();

    boost::filesystem::path output_filename = output_dir;
    output_filename /= "heat_solution";
    output_filename += ".vtu";

    std::ofstream out(output_filename.c_str());

    data_out.write_vtu(out);
}

