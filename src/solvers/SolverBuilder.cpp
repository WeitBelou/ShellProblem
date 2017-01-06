#include "SolverBuilder.hpp"
#include "HeatSolver.hpp"
#include "ElasticitySolver.hpp"
std::shared_ptr<SolverBase> SolverBuilder::create_solver(const json &solver_properties,
                                                         std::shared_ptr<MeshBase> mesh,
                                                         std::shared_ptr<LinearSolverBase> linear_solver,
                                                         BoundariesGroup boundaries)
{
    std::string problem_type = solver_properties["type"].get<std::string>();

    const json material = solver_properties["material"];

    if (problem_type == "simple_heat") {
        HeatSolver::Material heat(material["thermal_diffusivity"].get<double>());
        return std::make_shared<HeatSolver>(mesh, heat, boundaries, linear_solver);
    }
    else if (problem_type == "simple_elasticity") {
        ElasticitySolver::Material elasticity(material["E"].get<double>(),
                                              material["G"].get<double>());

        return std::make_shared<ElasticitySolver>(mesh, elasticity, boundaries, linear_solver);
    }
    else {
        AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented())
        return nullptr;
    };
}