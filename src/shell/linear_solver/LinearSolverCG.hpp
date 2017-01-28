#pragma once
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
