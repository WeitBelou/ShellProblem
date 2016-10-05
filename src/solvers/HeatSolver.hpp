#ifndef SHELL_PROBLEM_HEAT_SOLVER_HPP
#define SHELL_PROBLEM_HEAT_SOLVER_HPP

#include <boost/filesystem/path.hpp>

#include <deal.II/grid/tria.h>
#include <deal.II/base/function.h>

#include <deal.II/lac/vector.h>
#include <deal.II/lac/sparse_matrix.h>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/fe/fe_q.h>
#include <deal.II/base/quadrature_lib.h>
#include <deal.II/lac/constraint_matrix.h>

#include "launcher/SimpleMaterial.hpp"
#include "mesh/MeshWrappers.hpp"

namespace HeatSolver
{

class FairingBoundaryFunction : public dealii::Function<3>
{
public:

    FairingBoundaryFunction() : dealii::Function<3>(1){}

    double value(const dealii::Point<3> &point,
                 size_t component = 0) const override;
};

class SimpleSolver
{
public:
    SimpleSolver(const MeshWrappers::Mesh &mesh,
                 const Material::SimpleHeat &heat_properties);
    ~SimpleSolver();

    void run(const std::string &output_dir);

private:
    void setup_system();
    void assemble_system();
    size_t solve_linear_system();
    void output_solution(const boost::filesystem::path &output_dir);

    dealii::DoFHandler<3> dof_handler;

    const dealii::ZeroFunction<3> rhs_function;
    const FairingBoundaryFunction fairing_boundary_function;

    const dealii::FE_Q<3> fe;
    const dealii::QGauss<3> quadrature;

    const double a_square;

    dealii::ConstraintMatrix constraints;

    dealii::SparsityPattern sparsity_pattern;
    dealii::SparseMatrix<double> system_matrix;
    dealii::Vector<double> system_rhs;
    dealii::Vector<double> solution;
};

}


#endif //SHELL_PROBLEM_HEAT_SOLVER_HPP
