#include "SolverBuilder.hpp"
#include "HeatSolver.hpp"
#include "ElasticitySolver.hpp"
std::shared_ptr<SolverBase> SolverBuilder::create_solver(const json &solver_properties,
                                                        std::shared_ptr<MeshBase> mesh,
                                                        std::shared_ptr<LinearSolverBase> linear_solver,
                                                        BoundariesGroup boundaries,
                                                        MaterialsGroup materials)
{
    std::string problem_type = solver_properties["type"].get<std::string>();

    if (problem_type == "simple_heat") {
        return std::make_shared<HeatSolver>(mesh, materials, boundaries, linear_solver);
    }
    else if (problem_type == "simple_elasticity") {
        return std::make_shared<ElasticitySolver>(mesh, materials, boundaries, linear_solver);
    }
    else {
        AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented(
            std::string("Unknown problem type ") + problem_type + "."))
        return nullptr;
    };
}