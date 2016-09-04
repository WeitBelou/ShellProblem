#include "HeatSolver.hpp"

#include <deal.II/lac/dynamic_sparsity_pattern.h>

#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>

#include <deal.II/dofs/dof_accessor.h>
#include <deal.II/dofs/dof_tools.h>

#include <deal.II/fe/fe_values.h>

#include <deal.II/lac/solver.h>
#include <deal.II/lac/solver_control.h>
#include <deal.II/lac/precondition.h>

#include <deal.II/numerics/data_out.h>
#include <fstream>

using namespace dealii;

HeatSolver::SimpleSolver::SimpleSolver(dealii::Triangulation<3> &mesh,
                                       const dealii::Function<3> &rhs_function,
                                       const dealii::Function<3> &fairing_conditions,
                                       const double a_square)
    :
    mesh(&mesh),
    dof_handler(mesh),
    rhs_function(&rhs_function),
    fairing_conditions(&fairing_conditions),
    fe(2),
    quadrature(2),
    a_square(a_square)
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
    std::cout << "    Solver conerges in " << n_iter << " iterations." << std::endl;

    std::cout << "    Output solution..." << std::endl << std::flush;
    output_solution(output_dir);
}

void HeatSolver::SimpleSolver::setup_system()
{
    dof_handler.distribute_dofs(fe);

    DoFTools::make_hanging_node_constraints(dof_handler,
                                            hanging_node_constraints);

    DynamicSparsityPattern dsp(dof_handler.n_dofs());
    DoFTools::make_sparsity_pattern(dof_handler, dsp, hanging_node_constraints);
    sparsity_pattern.copy_from(dsp);

    system_matrix.reinit(sparsity_pattern);
    solution.reinit(dof_handler.n_dofs());
    system_rhs.reinit(dof_handler.n_dofs());
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
                    cell_matrix(i, j) += a_square * fe_values.shape_grad(i, q) *
                                         fe_values.shape_grad(j, q) *
                                         fe_values.JxW(q);
                }

                cell_rhs(i) += fe_values.shape_value(i, q) *
                               rhs_function->value(fe_values.quadrature_point(q)) *
                               fe_values.JxW(q);
            }
        }

        cell->get_dof_indices(local_dof_indices);

        hanging_node_constraints.distribute_local_to_global(cell_matrix,
                                                            cell_rhs,
                                                            local_dof_indices,
                                                            system_matrix,
                                                            system_rhs);
    }

    std::map<types::global_dof_index, double> boundary_values;

    VectorTools::interpolate_boundary_values(dof_handler,
                                             0,
                                             ZeroFunction<3>(1),
                                             boundary_values);

    VectorTools::interpolate_boundary_values(dof_handler,
                                             1,
                                             *fairing_conditions,
                                             boundary_values);

    MatrixTools::apply_boundary_values(boundary_values, system_matrix,
                                       solution, system_rhs);
}

size_t HeatSolver::SimpleSolver::solve_linear_system()
{
    SolverControl solver_control(dof_handler.n_dofs() / 2);
    SolverCG<> solver(solver_control);

    PreconditionSSOR<> preconditioner;
    preconditioner.initialize(system_matrix, 1.2);

    solver.solve(system_matrix, solution, system_rhs, preconditioner);

    return solver_control.last_step();
}

void HeatSolver::SimpleSolver::output_solution(const boost::filesystem::path &output_dir)
{
    DataOut<3> data_out;

    data_out.attach_dof_handler(dof_handler);
    data_out.add_data_vector(solution, "T");

    data_out.build_patches();

    boost::filesystem::path output_filename = output_dir;
    output_filename /= "heat_solution.vtu";

    std::ofstream out(output_filename.c_str());

    data_out.write_vtu(out);
}

