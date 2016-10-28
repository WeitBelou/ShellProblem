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

#include "launcher/SimpleMaterial.hpp"
#include "mesh/MeshWrappers.hpp"
#include "Boundaries.hpp"

namespace Solvers
{

class ElasticitySolver
{
public:
    ElasticitySolver(const MeshWrappers::Mesh &mesh,
                 const Material::SimpleElasticity &elasticity);
    ~ElasticitySolver();
    void run(const boost::filesystem::path &output_dir);
private:
    void setup_system();
    void assemble_system();
    size_t solve_linear_system();
    void output_solution(const boost::filesystem::path &output_dir);

    const dealii::SmartPointer<const dealii::Triangulation<3>> tria;
    dealii::DoFHandler<3> dof_handler;

    const dealii::FESystem<3> fe;
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
