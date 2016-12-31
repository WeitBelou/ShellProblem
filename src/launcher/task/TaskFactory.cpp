#include "TaskFactory.hpp"

#include <fstream>
#include "src/mesh/SimpleShellMesh.hpp"

#include "src/mesh/CubeMesh.hpp"
#include "src/solvers/postprocessors/OutputWriter.hpp"
#include "src/solvers/HeatSolver.hpp"

#include "src/solvers/ElasticitySolver.hpp"
#include "src/mesh/MeshFactory.hpp"

TaskFactory::TaskFactory(const std::string &output_dir)
    : output_dir(output_dir)
{

}

std::shared_ptr<Task> TaskFactory::create_task_from_json(json task) const
{
    const json &mesh_properties = task["mesh"];
    std::shared_ptr<Meshes::MeshBase> mesh = create_mesh(mesh_properties);

    const json &solver_properties = task["solver"];
    std::shared_ptr<Solvers::SolverBase> solver = create_solver(solver_properties, mesh);

    return std::make_shared<Task>(solver, output_dir);
}

std::shared_ptr<Meshes::MeshBase> TaskFactory::create_mesh(const json &mesh_properties) const
{
    std::string mesh_type = mesh_properties["type"].get<std::string>();

    const json geometry = mesh_properties["geometry"];

    if (mesh_type == "cube") {
        return MeshFactory::create_cube_mesh(geometry);
    }
    else if (mesh_type == "simple_shell") {
        return MeshFactory::create_simple_shell_mesh(geometry);
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented());
        return nullptr;
    }
}
std::shared_ptr<Solvers::SolverBase>
TaskFactory::create_solver(const json &solver_properties, std::shared_ptr<Meshes::MeshBase> mesh) const
{
    std::string problem_type = solver_properties["type"].get<std::string>();

    const json material = solver_properties["material"];
    if (problem_type == "simple_heat") {
        Solvers::HeatSolver::Material heat(material["thermal_diffusivity"].get<double>());
        return std::make_shared<Solvers::HeatSolver>(mesh, heat);
    }
    else if (problem_type == "simple_elasticity") {
        Solvers::ElasticitySolver::Material elasticity(material["E"].get<double>(),
                                                       material["G"].get<double>());

        json linear_solver_properties = solver_properties["linear_solver_data"];
        dealii::SolverGMRES<>::AdditionalData linear_solver_data = get_gmres_additional_data(linear_solver_properties);
        return std::make_shared<Solvers::ElasticitySolver>(mesh, elasticity, linear_solver_data);
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented())
        return nullptr;
    };
}
dealii::SolverGMRES<>::AdditionalData TaskFactory::get_gmres_additional_data(const json &linear_solver_properties) const
{
    return dealii::SolverGMRES<>::AdditionalData
        {linear_solver_properties["max_n_tmp_vectors"].get<unsigned>(),
         linear_solver_properties["right_preconditioning"].get<bool>(),
         linear_solver_properties["use_default_residual"].get<bool>(),
         linear_solver_properties["force_re_orthogonalization"].get<bool>()
        };
}

