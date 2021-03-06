#include "ElasticitySolver.hpp"

#include <deal.II/fe/fe_q.h>

#include <deal.II/fe/fe_values.h>

#include <deal.II/dofs/dof_tools.h>
#include <deal.II/lac/dynamic_sparsity_pattern.h>

#include <deal.II/numerics/vector_tools.h>
#include "src/shell/postprocessors/OutputWriter.hpp"


using namespace dealii;

ElasticitySolver::ElasticitySolver(std::shared_ptr<MeshBase> mesh,
                                   const MaterialsGroup &materials,
                                   const BoundariesGroup boundaries,
                                   std::shared_ptr<LinearSolverBase> linear_solver)
    :
    SolverBase(mesh),
    boundaries(boundaries),
    materials(materials),
    linear_solver(linear_solver),
    dof_handler(this->mesh->mesh()),
    fe(FE_Q<3>(1), 3),
    displacement_extractor(0),
    quadrature(2),
    face_quadrature(2)
{

}

ElasticitySolver::~ElasticitySolver()
{
    dof_handler.clear();
}

void ElasticitySolver::setup_system()
{
    dof_handler.distribute_dofs(fe);

    constraints.clear();
    boundaries.apply_dirichlet(dof_handler, constraints);
    constraints.close();

    DynamicSparsityPattern dsp(dof_handler.n_dofs(), dof_handler.n_dofs());
    DoFTools::make_sparsity_pattern(dof_handler, dsp,
                                    constraints, false);
    sparsity_pattern.copy_from(dsp);

    system_matrix.reinit(sparsity_pattern);
    system_rhs.reinit(dof_handler.n_dofs());
    displacement.reinit(dof_handler.n_dofs());
}

void ElasticitySolver::assemble_system()
{
    system_matrix = 0;
    system_rhs = 0;

    FEValues<3> fe_values(fe, quadrature,
                          update_values | update_gradients
                              | update_JxW_values);

    FEFaceValues<3> fe_face_values(fe, face_quadrature,
                                   update_values | update_face_normal_vectors |
                                       update_quadrature_points | update_JxW_values);

    const unsigned int dofs_per_cell = fe.dofs_per_cell;
    const unsigned int n_q_points = quadrature.size();
    const unsigned int n_face_q_points = face_quadrature.size();

    FullMatrix<double> cell_matrix(dofs_per_cell, dofs_per_cell);
    Vector<double> cell_rhs(dofs_per_cell);
    std::vector<types::global_dof_index> local_dof_indices(dofs_per_cell);

    for (auto cell: dof_handler.active_cell_iterators()) {
        cell_matrix = 0;
        cell_rhs = 0;

        fe_values.reinit(cell);

        auto material = materials.get_material_by_id(cell->material_id());
        auto stress_strain = material->get_stress_strain_tensor();
        //Assemble matrix
        for (unsigned int q = 0; q < n_q_points; ++q) {
            const double jxw = fe_values.JxW(q);
            for (unsigned int i = 0; i < dofs_per_cell; ++i) {
                for (unsigned int j = 0; j < dofs_per_cell; ++j) {
                    const SymmetricTensor<2, 3> eps_phi_i = fe_values[displacement_extractor].symmetric_gradient(i, q);
                    const SymmetricTensor<2, 3> eps_phi_j = fe_values[displacement_extractor].symmetric_gradient(j, q);

                    cell_matrix(i, j) += eps_phi_i * stress_strain * eps_phi_j * jxw;
                }
            }
        }

        //Assemble rhs
        for (unsigned int f = 0; f < GeometryInfo<3>::faces_per_cell; ++f) {
            for (const auto &it: boundaries.get_neumann()) {
                if (cell->face(f)->at_boundary() && cell->face(f)->boundary_id() == it.first) {
                    fe_face_values.reinit(cell, f);

                    std::vector<double> pressure(n_face_q_points);
                    it.second->value_list(fe_face_values.get_quadrature_points(), pressure);

                    for (unsigned int i = 0; i < dofs_per_cell; ++i) {
                        const unsigned int component_i = fe.system_to_component_index(i).first;

                        for (unsigned int q = 0; q < n_face_q_points; ++q) {
                            cell_rhs(i) += -pressure[q] *
                                fe_face_values.shape_value(i, q) *
                                fe_face_values.normal_vector(q)[component_i] *
                                fe_face_values.JxW(q);
                        }
                    }
                }
            }
        }
        cell->get_dof_indices(local_dof_indices);
        constraints.distribute_local_to_global(cell_matrix, cell_rhs,
                                               local_dof_indices,
                                               system_matrix, system_rhs);
    }
}

unsigned int ElasticitySolver::solve_linear_system()
{
    auto res = linear_solver->solve(system_matrix, system_rhs);
    displacement = res.result;
    constraints.distribute(displacement);
    return res.control.last_step();
}

std::vector<std::vector<dealii::Vector<double>>> ElasticitySolver::compute_stress_tensor()
{
    std::vector<std::vector<dealii::Vector<double>>>
        s(3, std::vector<dealii::Vector<double>>(3, dealii::Vector<double>(mesh->mesh().n_active_cells())));
    FEValues<3> fe_values(fe, quadrature,
                          update_values | update_gradients);
    std::vector<SymmetricTensor<2, 3>> displacement_grads(quadrature.size());

    const size_t n_q_points = quadrature.size();

    for (auto cell : dof_handler.active_cell_iterators()) {
        fe_values.reinit(cell);

        auto stress_strain = materials.get_material_by_id(cell->material_id())->get_stress_strain_tensor();

        fe_values[displacement_extractor].get_function_symmetric_gradients(displacement, displacement_grads);
        SymmetricTensor<2, 3> stress;
        for (unsigned int q = 0; q < n_q_points; ++q) {
            stress += stress_strain * displacement_grads[q];
        }

        for (unsigned i = 0; i < 3; ++i) {
            for (unsigned j = 0; j < 3; ++j) {
                s[i][j][cell->active_cell_index()] = stress[i][j] / n_q_points;
            }
        }
    }
    return std::move(s);
}

Vector<double> ElasticitySolver::compute_norm_of_stress()
{
    Vector<double> norm_of_stress(mesh->mesh().n_active_cells());
    FEValues<3> fe_values(fe, quadrature,
                          update_values | update_gradients);
    std::vector<SymmetricTensor<2, 3>> displacement_grads(quadrature.size());

    const size_t n_q_points = quadrature.size();

    for (auto cell : dof_handler.active_cell_iterators()) {
        fe_values.reinit(cell);

        auto stress_strain = materials.get_material_by_id(cell->material_id())->get_stress_strain_tensor();

        fe_values[displacement_extractor].get_function_symmetric_gradients(displacement, displacement_grads);
        SymmetricTensor<2, 3> stress;
        for (unsigned int q = 0; q < n_q_points; ++q) {
            stress += stress_strain * displacement_grads[q];
        }
        norm_of_stress(cell->active_cell_index()) = stress.norm() / n_q_points;
    }
    return norm_of_stress;
}

void ElasticitySolver::do_postprocessing(const std::string &output_dir)
{
    OutputWriter writer{dof_handler};
    deallog << "Output displacement..." << std::endl;
    writer.add_vector_data(displacement, "displacement");

    deallog << "Compute stress tensor..." << std::endl;
    auto s = compute_stress_tensor();

    deallog << "Output stress tensor..." << std::endl;
    writer.add_matrix_data(s, "s");

    deallog << "Compute norm of stress..." << std::endl;
    auto norm_of_stress = compute_norm_of_stress();

    deallog << "Output norm of stress..." << std::endl;
    writer.add_scalar_data(norm_of_stress, "norm_of_stress");

    writer.write_results(output_dir, "results");
}

unsigned int ElasticitySolver::get_n_dofs()
{
    return dof_handler.n_dofs();
}
