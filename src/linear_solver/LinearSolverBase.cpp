#include "LinearSolverBase.hpp"

LinearSolverBase::LinearSolverBase(const double eps, const unsigned int n_steps)
    :
    solver_control(n_steps, eps, true, true)
{

}
