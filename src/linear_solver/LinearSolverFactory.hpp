#ifndef SHELL_PROBLEM_LINEAR_SOLVER_FACTORY_HPP
#define SHELL_PROBLEM_LINEAR_SOLVER_FACTORY_HPP

#include <memory>
#include "LinearSolverBase.hpp"
#include "src/task/TaskUtil.hpp"

class LinearSolverFactory
{
public:
    static std::shared_ptr<LinearSolverBase> create_linear_solver(const json &linear_solver_properties);
private:
    static dealii::SolverCG<>::AdditionalData create_cg_additional_data(const json &additional_data);
};


#endif //SHELL_PROBLEM_LINEAR_SOLVER_FACTORY_HPP
