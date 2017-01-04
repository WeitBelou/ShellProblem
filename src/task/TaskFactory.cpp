#include "TaskFactory.hpp"

#include <fstream>
#include <src/linear_solver/LinearSolverFactory.hpp>

#include "src/solvers/HeatSolver.hpp"

#include "src/solvers/ElasticitySolver.hpp"
#include "src/mesh/MeshFactory.hpp"
#include "src/boundaries/BoundariesFactory.hpp"

std::shared_ptr<Task> TaskFactory::create_task_from_json(json task, const std::string &output_dir)
{
    const json &mesh_properties = task["mesh"];
    std::shared_ptr<MeshBase> mesh = MeshFactory::create_mesh(mesh_properties);

    const json &linear_solver_properties = task["linear_solver"];
    std::shared_ptr<LinearSolverBase>
        linear_solver = LinearSolverFactory::create_linear_solver(linear_solver_properties);

    const json &solver_properties = task["solver"];
    std::shared_ptr<SolverBase> solver = create_solver(solver_properties, mesh, linear_solver);

    return std::make_shared<Task>(solver, output_dir);
}

std::shared_ptr<SolverBase>
TaskFactory::create_solver(const json &solver_properties,
                          std::shared_ptr<MeshBase> mesh,
                          std::shared_ptr<LinearSolverBase> linear_solver)
{
    std::string problem_type = solver_properties["type"].get<std::string>();

    BoundariesMap boundaries = BoundariesFactory::create_boundaries(solver_properties);

    const json material = solver_properties["material"];

    if (problem_type == "simple_heat") {
        HeatSolver::Material heat(material["thermal_diffusivity"].get<double>());
        return std::make_shared<HeatSolver>(mesh, heat, boundaries, linear_solver);
    }
    else if (problem_type == "simple_elasticity") {
        ElasticitySolver::Material elasticity(material["E"].get<double>(),
                                              material["G"].get<double>());
        json linear_solver_properties = solver_properties["linear_solver_data"];
        dealii::SolverGMRES<>::AdditionalData linear_solver_data = get_gmres_additional_data(linear_solver_properties);
        return std::make_shared<ElasticitySolver>(mesh, elasticity, boundaries, linear_solver_data);
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented())
        return nullptr;
    };
}
dealii::SolverGMRES<>::AdditionalData TaskFactory::get_gmres_additional_data(const json &linear_solver_properties)
{
    return dealii::SolverGMRES<>::AdditionalData
        {linear_solver_properties["max_n_tmp_vectors"].get<unsigned>(),
         linear_solver_properties["right_preconditioning"].get<bool>(),
         linear_solver_properties["use_default_residual"].get<bool>(),
         linear_solver_properties["force_re_orthogonalization"].get<bool>()
        };
}

