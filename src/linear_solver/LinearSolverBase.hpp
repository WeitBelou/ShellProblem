#ifndef SHELL_PROBLEM_LINEAR_SOLVER_BASE_HPP
#define SHELL_PROBLEM_LINEAR_SOLVER_BASE_HPP


#include <deal.II/lac/vector.h>
#include <deal.II/lac/solver_control.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/solver_cg.h>

class Result
{
public:
    dealii::SolverControl control;
    dealii::Vector<double> result;
};

class LinearSolverBase
{
public:
    LinearSolverBase(const double eps, const unsigned int n_steps);
    virtual ~LinearSolverBase() = default;
    virtual Result solve(const dealii::SparseMatrix<double> &a,
                         const dealii::Vector<double> &b) = 0;
protected:
    dealii::SolverControl solver_control;
};


#endif //SHELL_PROBLEM_LINEAR_SOLVER_BASE_HPP
