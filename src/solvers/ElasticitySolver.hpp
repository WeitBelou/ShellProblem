#ifndef SHELL_PROBLEM_ELASTICITY_SOLVER_HPP
#define SHELL_PROBLEM_ELASTICITY_SOLVER_HPP

#include <boost/filesystem/path.hpp>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/fe/fe_system.h>
#include <deal.II/base/quadrature_lib.h>
#include <deal.II/base/symmetric_tensor.h>

#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/sparsity_pattern.h>
#include <deal.II/lac/constraint_matrix.h>

#include "src/material/SimpleMaterial.hpp"
#include "mesh/CubeMesh.hpp"
#include "Boundaries.hpp"
#include "SolverBase.hpp"
#include "src/mesh/MeshBase.hpp"

namespace Solvers
{

class ElasticitySolver: public SolverBase
{
public:
    ElasticitySolver(std::shared_ptr<Meshes::MeshBase> mesh,
                     const Material::SimpleElasticity &elasticity,
                     const boost::filesystem::path &output_dir);
    ~ElasticitySolver();
protected:
    void setup_system() override;
    void assemble_system() override;
    unsigned int solve_linear_system() override;
    void do_postprocessing() override;
    unsigned int get_n_dofs() override;
private:
    void compute_norm_of_stress();
    void output_solution(const boost::filesystem::path &output_dir);

    const boost::filesystem::path &output_dir;

    dealii::DoFHandler<3> dof_handler;

    dealii::Vector<double> norm_of_stress;
    const dealii::FESystem<3> fe;
    const dealii::FEValuesExtractors::Vector displacement;
    const dealii::QGauss<3> quadrature;

    const dealii::QGauss<2> face_quadrature;

    dealii::ConstraintMatrix constraints;
    const dealii::SymmetricTensor<4, 3> stress_strain;

    const SinSquare fairing_function;

    dealii::SparsityPattern sparsity_pattern;
    dealii::SparseMatrix<double> system_matrix;
    dealii::Vector<double> system_rhs;

    dealii::Vector<double> solution;
};

}


#endif //SHELL_PROBLEM_ELASTICITY_SOLVER_HPP
