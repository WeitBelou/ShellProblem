#include <fstream>
#include <src/mesh/SimpleShellMesh.hpp>
#include "src/solvers/HeatSolver.hpp"
#include "src/solvers/ElasticitySolver.hpp"
#include "TaskFactory.hpp"

using json = nlohmann::json;

std::shared_ptr<Task> TaskFactory::create_task(const std::string &task_file, const std::string &output_dir) const
{
    json j = get_json(task_file);
    std::shared_ptr<Meshes::MeshBase> mesh = create_mesh(j["mesh"]);
    std::shared_ptr<Solvers::SolverBase> solver = create_solver(j["solver"], mesh, output_dir);

    return std::make_shared<Task>(solver);
}

json TaskFactory::get_json(const std::string &task_file) const
{
    json j;
    std::ifstream input(task_file);
    input >> j;
    return j;
}

std::shared_ptr<Meshes::MeshBase> TaskFactory::create_mesh(const json &mesh_properties) const
{
    std::string mesh_type = mesh_properties["type"].get<std::string>();
    const json geometry = mesh_properties["geometry"];
    if (mesh_type == "cube") {
        return std::make_shared<Meshes::CubeMesh>(
            geometry["size"].get<double>(),
            geometry["n_refines"].get<unsigned>());
    }
    else if (mesh_type == "simple_shell") {
        const json sizes = geometry["sizes"];
        return std::make_shared<Meshes::SimpleShellMesh>(
            sizes["inner_radius"].get<double>(),
            sizes["outer_radius"].get<double>(),
            sizes["cylinder_length"].get<double>(),
            geometry["n_refines"].get<unsigned>()
        );
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented());
        return nullptr;
    }
}

std::shared_ptr<Solvers::SolverBase>
TaskFactory::create_solver(const json &solver_properties,
                           std::shared_ptr<Meshes::MeshBase> mesh,
                           const std::string &output_dir) const
{
    std::string problem_type = solver_properties["type"].get<std::string>();

    const json material = solver_properties["material"];
    if (problem_type == "simple_heat") {
        Material::SimpleHeat heat(material["thermal_diffusivity"].get<double>());
        return std::make_shared<Solvers::HeatSolver>(mesh, heat, output_dir);
    }
    else if (problem_type == "simple_elasticity") {
        Material::SimpleElasticity elasticity(material["E"].get<double>(),
                                              material["G"].get<double>());
        return std::make_shared<Solvers::ElasticitySolver>(mesh, elasticity, output_dir);
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented())
        return nullptr;
    };
}

