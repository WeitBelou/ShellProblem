#include "LinearSolverFactory.hpp"
#include "LinearSolverCG.hpp"

std::shared_ptr<LinearSolverBase> LinearSolverFactory::create_linear_solver(const json &linear_solver_properties)
{
    const std::string type = linear_solver_properties["type"].get<std::string>();

    const double eps = linear_solver_properties["eps"].get<double>();
    const double n_steps = linear_solver_properties["n_steps"].get<int>();
    const json additional_data = linear_solver_properties["additional_data"];

    if (type == "CG") {
        return std::make_shared<LinearSolverCG>(eps, n_steps, create_cg_additional_data(additional_data));
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented());
        return nullptr;
    }
}

dealii::SolverCG::AdditionalData LinearSolverFactory::create_cg_additional_data(const json &additional_data)
{
    return dealii::SolverCG::AdditionalData();
}
