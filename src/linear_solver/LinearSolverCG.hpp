#ifndef SHELL_PROBLEM_LINEAR_SOLVER_CG_HPP
#define SHELL_PROBLEM_LINEAR_SOLVER_CG_HPP

#include <deal.II/lac/solver_cg.h>
#include "LinearSolverBase.hpp"

class LinearSolverCG: public LinearSolverBase
{
public:
    LinearSolverCG(const double eps,
                   const unsigned int n_steps,
                   const dealii::SolverCG<>::AdditionalData &data);

    Result solve(const dealii::SparseMatrix<double> &a,
                 const dealii::Vector<double> &b) override;
private:
    dealii::SolverCG<> solver;
};


#endif //SHELL_PROBLEM_LINEAR_SOLVER_CG_HPP
