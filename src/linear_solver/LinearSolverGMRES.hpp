#pragma once
#include <deal.II/lac/solver_gmres.h>

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
