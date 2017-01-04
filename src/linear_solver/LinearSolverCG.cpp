#include "LinearSolverCG.hpp"
#include <deal.II/lac/precondition.h>

LinearSolverCG::LinearSolverCG(const double eps,
                               const unsigned int n_steps,
                               const dealii::SolverCG<>::AdditionalData &data)
    :
    LinearSolverBase(eps, n_steps),
    solver(solver_control, data)
{

}

Result LinearSolverCG::solve(const dealii::SparseMatrix<double> &a, const dealii::Vector<double> &b)
{
    dealii::Vector<double> solution(static_cast<const unsigned int>(b.size()));

    dealii::PreconditionSSOR<> preconditioner;
    preconditioner.initialize(a, 1.2);

    solver.solve(a, solution, b, preconditioner);
    return {solver_control, solution};
}
