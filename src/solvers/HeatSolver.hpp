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

namespace HeatSolver
{

class SimpleSolver
{
public:
    SimpleSolver(dealii::Triangulation<3> &mesh,
                 const dealii::Function<3> &rhs_function,
                 const dealii::Function<3> &fairing_conditions,
                 const double a_square);
    ~SimpleSolver();

    void run(const boost::filesystem::path &output_dir);

private:
    void setup_system();
    void assemble_system();
    size_t solve_linear_system();
    void output_solution(const boost::filesystem::path &output_dir);

    const dealii::SmartPointer<dealii::Triangulation<3>> mesh;
    dealii::DoFHandler<3> dof_handler;

    const dealii::SmartPointer<const dealii::Function<3>> rhs_function;
    const dealii::SmartPointer<const dealii::Function<3>> fairing_conditions;

    const dealii::FE_Q<3> fe;
    const dealii::QGauss<3> quadrature;

    const double a_square;

    dealii::ConstraintMatrix hanging_node_constraints;
    dealii::SparsityPattern sparsity_pattern;
    dealii::SparseMatrix<double> system_matrix;
    dealii::Vector<double> system_rhs;
    dealii::Vector<double> solution;
};

}


#endif //SHELL_PROBLEM_HEAT_SOLVER_HPP
