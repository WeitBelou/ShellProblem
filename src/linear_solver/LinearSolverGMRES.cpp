#include <deal.II/lac/solver_gmres.h>
#include <deal.II/lac/precondition.h>
#include "LinearSolverGMRES.hpp"
#include "LinearSolverBase.hpp"
LinearSolverGMRES::LinearSolverGMRES(const double eps,
                                     const unsigned int n_steps,
                                     const dealii::SolverGMRES<>::AdditionalData &data)
    :
    LinearSolverBase(eps, n_steps),
    solver(solver_control, data)
{

}
Result LinearSolverGMRES::solve(const dealii::SparseMatrix<double> &a, const dealii::Vector<double> &b)
{
    dealii::Vector<double> solution(static_cast<const unsigned int>(b.size()));

    dealii::PreconditionIdentity preconditioner;
    preconditioner.initialize(a);

    solver.solve(a, solution, b, dealii::PreconditionIdentity());
    return {solver_control, solution};
}
