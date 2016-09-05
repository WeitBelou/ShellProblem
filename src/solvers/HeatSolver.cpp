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

HeatSolver::SimpleSolver::SimpleSolver(dealii::Triangulation<3> &mesh,
                                       const TaskReader::HeatProperties &heat_properties)
    :
    mesh(&mesh),
    dof_handler(mesh),
    rhs_function(&heat_properties.rhs_function),
    fairing_conditions(&heat_properties.fairing_boundary_function),
    outer_boundary_conditions(&heat_properties.other_boundary_function),
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
    for (size_t step = 0; step < 3; ++step)
    {
        std::cout << "Refinement step: " << step << std::endl;

        std::cout << "    Setup system..." << std::endl << std::flush;
        setup_system();
        std::cout << "    Number of degrees of freedom: " << dof_handler.n_dofs() << std::endl;

        std::cout << "    Assembling system..." << std::endl << std::flush;
        assemble_system();

        std::cout << "    Solving linear system..." << std::endl << std::flush;
        const size_t n_iter = solve_linear_system();
        std::cout << "    Solver converges in " << n_iter << " iterations." << std::endl;

        std::cout << "    Output solution..." << std::endl << std::flush;
        output_solution(output_dir, step);

        std::cout << "    Refine mesh..." << std::endl << std::flush;
        refine_grid();
    }

}

void HeatSolver::SimpleSolver::setup_system()
{
    dof_handler.distribute_dofs(fe);

    solution.reinit(dof_handler.n_dofs());
    system_rhs.reinit(dof_handler.n_dofs());

    constraints.clear();

    DoFTools::make_hanging_node_constraints(dof_handler, constraints);

    VectorTools::interpolate_boundary_values(dof_handler,
                                             0,
                                             *outer_boundary_conditions,
                                             constraints);

    VectorTools::interpolate_boundary_values(dof_handler,
                                             1,
                                             *outer_boundary_conditions,
                                             constraints);
    VectorTools::interpolate_boundary_values(dof_handler,
                                             2,
                                             *fairing_conditions,
                                             constraints);
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

void HeatSolver::SimpleSolver::refine_grid()
{
    Vector<float> estimated_error_per_cell(mesh->n_active_cells());
    KellyErrorEstimator<3>::estimate(dof_handler,
                                     QGauss<2>(3),
                                     FunctionMap<3>::type(),
                                     solution,
                                     estimated_error_per_cell);

    GridRefinement::refine_and_coarsen_fixed_number(*mesh, estimated_error_per_cell, 0.3, 0);
    mesh->execute_coarsening_and_refinement();
}

void HeatSolver::SimpleSolver::output_solution(const boost::filesystem::path &output_dir, size_t refinement_step)
{
    DataOut<3> data_out;

    data_out.attach_dof_handler(dof_handler);
    data_out.add_data_vector(solution, "T");

    data_out.build_patches();

    boost::filesystem::path output_filename = output_dir;
    output_filename /= "heat_solution-";
    output_filename += Utilities::int_to_string(refinement_step, 2);
    output_filename += ".vtu";

    std::ofstream out(output_filename.c_str());

    data_out.write_vtu(out);
}

