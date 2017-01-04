#ifndef SHELL_PROBLEM_LINEAR_SOLVER_GMRES_HPP
#define SHELL_PROBLEM_LINEAR_SOLVER_GMRES_HPP

#include "LinearSolverBase.hpp"

class LinearSolverGMRES: public LinearSolverBase
{
public:
    LinearSolverGMRES(const double eps,
                      const unsigned int n_steps,
                      const dealii::SolverGMRES<>::AdditionalData &data);
    Result solve(const dealii::SparseMatrix<double> &a, const dealii::Vector<double> &b) override;
private:
    dealii::SolverGMRES<> solver;
};


#endif //SHELL_PROBLEM_LINEAR_SOLVER_GMRES_HPP
