#include "HeatSolver.hpp"
#include <deal.II/lac/dynamic_sparsity_pattern.h>

#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>

#include <deal.II/dofs/dof_tools.h>

#include <deal.II/fe/fe_values.h>

#include <deal.II/lac/precondition.h>
#include <deal.II/numerics/data_out.h>
#include <src/shell/materials/MaterialsGroup.hpp>

#include "src/shell/postprocessors/OutputWriter.hpp"

using namespace dealii;

HeatSolver::HeatSolver(std::shared_ptr<MeshBase> mesh,
                       const MaterialsGroup &materials,
                       const BoundariesGroup boundaries,
                       const std::shared_ptr<LinearSolverBase> &linear_solver)
    :
    SolverBase(mesh),
    materials(materials),
    boundaries(boundaries),
    linear_solver(linear_solver),
    dof_handler(this->mesh->mesh()),
    fe(2),
    quadrature(2),
    face_quadrature(2)
{

}

HeatSolver::~HeatSolver()
{
    dof_handler.clear();
}

void HeatSolver::setup_system()
{
    dof_handler.distribute_dofs(fe);

    solution.reinit(dof_handler.n_dofs());
    system_rhs.reinit(dof_handler.n_dofs());


    constraints.clear();
    boundaries.apply_dirichlet(dof_handler, constraints);
    constraints.close();

    DynamicSparsityPattern dsp(dof_handler.n_dofs());
    DoFTools::make_sparsity_pattern(dof_handler, dsp, constraints, true);
    sparsity_pattern.copy_from(dsp);

    system_matrix.reinit(sparsity_pattern);
}

void HeatSolver::assemble_system()
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

        cell->get_dof_indices(local_dof_indices);
        constraints.distribute_local_to_global(cell_matrix,
                                               cell_rhs,
                                               local_dof_indices,
                                               system_matrix,
                                               system_rhs);
    }
}

unsigned int HeatSolver::solve_linear_system()
{
    auto res = linear_solver->solve(system_matrix, system_rhs);
    solution = res.result;
    constraints.distribute(solution);
    return res.control.last_step();
}

void HeatSolver::do_postprocessing(const std::string &output_dir)
{
    dealii::deallog << "Output temperature..." << std::endl;
    OutputWriter writer{dof_handler};
    writer.add_scalar_data(solution, "T");
    writer.write_results(output_dir, "results");
}

unsigned int HeatSolver::get_n_dofs()
{
    return dof_handler.n_dofs();
}
