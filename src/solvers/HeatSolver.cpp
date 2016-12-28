#include "HeatSolver.hpp"

#include <deal.II/lac/dynamic_sparsity_pattern.h>

#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>

#include <deal.II/dofs/dof_tools.h>

#include <deal.II/fe/fe_values.h>

#include <deal.II/lac/solver.h>
#include <deal.II/lac/precondition.h>
#include <deal.II/numerics/data_out.h>
#include <fstream>

using namespace dealii;

Solvers::HeatSolver::HeatSolver(const MeshWrappers::Mesh &mesh,
                                const Material::SimpleHeat &heat_properties,
                                const boost::filesystem::path &output_dir)
    :
    output_dir(output_dir),
    dof_handler(mesh.mesh()),
    fairing_function(2000),
    fe(2),
    quadrature(2),
    face_quadrature(2)
{

}

Solvers::HeatSolver::~HeatSolver()
{
    dof_handler.clear();
}

void Solvers::HeatSolver::setup_system()
{
    dof_handler.distribute_dofs(fe);

    solution.reinit(dof_handler.n_dofs());
    system_rhs.reinit(dof_handler.n_dofs());


    ConstraintMatrix dirichlet_boundary_constraints;
    dirichlet_boundary_constraints.clear();
    VectorTools::interpolate_boundary_values(dof_handler, 0, ZeroFunction<3>(1),
                                             dirichlet_boundary_constraints);
    VectorTools::interpolate_boundary_values(dof_handler, 1, fairing_function,
                                             dirichlet_boundary_constraints);
    dirichlet_boundary_constraints.close();

    constraints.clear();
    DoFTools::make_hanging_node_constraints(dof_handler, constraints);
    constraints.merge(dirichlet_boundary_constraints, ConstraintMatrix::right_object_wins);
    constraints.close();

    DynamicSparsityPattern dsp(dof_handler.n_dofs());
    DoFTools::make_sparsity_pattern(dof_handler, dsp, constraints, true);
    sparsity_pattern.copy_from(dsp);

    system_matrix.reinit(sparsity_pattern);
}

void Solvers::HeatSolver::assemble_system()
{
    FEValues<3> fe_values(fe, quadrature,
                          update_values | update_gradients |
                              update_quadrature_points | update_JxW_values);

    QGauss<2> face_quadrature(2);
    FEFaceValues<3> fe_face_values(fe, face_quadrature,
                                   update_values | update_quadrature_points |
                                       update_normal_vectors | update_JxW_values);

    const unsigned int dofs_per_cell = fe.dofs_per_cell;
    const unsigned int n_q_points = quadrature.size();
    const unsigned int n_face_q_points = face_quadrature.size();

    FullMatrix<double> cell_matrix(dofs_per_cell, dofs_per_cell);
    Vector<double> cell_rhs(dofs_per_cell);

    std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);

    for (auto cell : dof_handler.active_cell_iterators()) {
        fe_values.reinit(cell);

        cell_matrix = 0;
        cell_rhs = 0;

        for (unsigned int q = 0; q < n_q_points; ++q) {
            for (unsigned int i = 0; i < dofs_per_cell; ++i) {
                const Tensor<1, 3> grad_phi_i = fe_values.shape_grad(i, q);

                for (unsigned int j = 0; j < dofs_per_cell; ++j) {
                    const Tensor<1, 3> grad_phi_j = fe_values.shape_grad(j, q);

                    cell_matrix(i, j) += grad_phi_i *
                        grad_phi_j *
                        fe_values.JxW(q);
                }
            }
        }

        for (unsigned int f = 0; f < GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary() && cell->face(f)->boundary_id() == 1) {
                fe_face_values.reinit(cell, f);
                for (unsigned int q = 0; q < n_face_q_points; ++q) {
                    const double boundary_value = fairing_function.gradient(fe_face_values.quadrature_point(q))
                        * fe_face_values.normal_vector(q);
                    for (unsigned int i = 0; i < dofs_per_cell; ++i) {
                        const double phi_i = fe_face_values.shape_value(i, q);
                        cell_rhs(i) += boundary_value * phi_i * fe_face_values.JxW(q);
                    }
                }
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

unsigned int Solvers::HeatSolver::solve_linear_system()
{
    SolverControl solver_control(dof_handler.n_dofs(), 1e-3);
    SolverCG<> solver(solver_control);

    PreconditionSSOR<> preconditioner;
    preconditioner.initialize(system_matrix, 1.2);

    constraints.set_zero(solution);
    solver.solve(system_matrix, solution, system_rhs, preconditioner);
    constraints.distribute(solution);

    return solver_control.last_step();
}

void Solvers::HeatSolver::output_solution(const boost::filesystem::path &output_dir)
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

void Solvers::HeatSolver::do_postprocessing()
{

    std::cout << "    Output solution..." << std::endl << std::flush;
    output_solution(output_dir);

}

unsigned int Solvers::HeatSolver::get_n_dofs()
{
    return dof_handler.n_dofs();
}
