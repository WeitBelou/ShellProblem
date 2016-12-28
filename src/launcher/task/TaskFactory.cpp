#include "TaskFactory.hpp"

#include <fstream>
#include <src/mesh/SimpleShellMesh.hpp>

#include <src/mesh/CubeMesh.hpp>
#include <src/solvers/postprocessors/OutputWriter.hpp>
#include "src/solvers/HeatSolver.hpp"

#include "src/solvers/ElasticitySolver.hpp"

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
        Solvers::HeatSolver::Material heat(material["thermal_diffusivity"].get<double>());
        std::vector<std::shared_ptr<Postprocessor>> postprocessors{std::make_shared<OutputWriter>(output_dir, "T")};
        return std::make_shared<Solvers::HeatSolver>(mesh, heat, postprocessors);
    }
    else if (problem_type == "simple_elasticity") {
        Solvers::ElasticitySolver::Material elasticity(material["E"].get<double>(),
                                                       material["G"].get<double>());
        std::vector<std::shared_ptr<Postprocessor>> postprocessors{std::make_shared<OutputWriter>(output_dir,
                                                                                                  "norm_of_stress")};
        return std::make_shared<Solvers::ElasticitySolver>(mesh, elasticity, postprocessors);
    }
    else {
        AssertThrow(false, dealii::ExcNotImplemented())
        return nullptr;
    };
}

