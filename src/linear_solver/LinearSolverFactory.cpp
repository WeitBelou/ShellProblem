#include "LinearSolverFactory.hpp"
#include "LinearSolverCG.hpp"
#include "LinearSolverGMRES.hpp"

std::shared_ptr<LinearSolverBase> LinearSolverFactory::create_linear_solver(const json &linear_solver_properties)
{
    const std::string type = linear_solver_properties["type"].get<std::string>();

    const double eps = linear_solver_properties["eps"].get<double>();
    const double n_steps = linear_solver_properties["n_steps"].get<int>();
    const json additional_data = linear_solver_properties["additional_data"];

    if (type == "CG") {
        return std::make_shared<LinearSolverCG>(eps, n_steps, create_cg_additional_data(additional_data));
    }
    else if (type == "GMRES") {
        return std::make_shared<LinearSolverGMRES>(eps, n_steps, create_gmres_additional_data(additional_data));
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented(
            std::string("Solver with type " +
                type + " doesn\'t exist.")));
        return nullptr;
    }
}

dealii::SolverCG<>::AdditionalData LinearSolverFactory::create_cg_additional_data(const json &additional_data)
{
    return dealii::SolverCG<>::AdditionalData();
}
dealii::SolverGMRES<>::AdditionalData LinearSolverFactory::create_gmres_additional_data(const json &additional_data)
{
    return dealii::SolverGMRES<>::AdditionalData
        {additional_data["max_n_tmp_vectors"].get<unsigned>(),
         additional_data["right_preconditioning"].get<bool>(),
         additional_data["use_default_residual"].get<bool>(),
         additional_data["force_re_orthogonalization"].get<bool>()
        };
}