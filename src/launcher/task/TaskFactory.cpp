#include <fstream>
#include "src/solvers/HeatSolver.hpp"
#include "src/solvers/ElasticitySolver.hpp"
#include "TaskFactory.hpp"

using json = nlohmann::json;

std::shared_ptr<Task> TaskFactory::create_task(const std::string &task_file, const std::string &output_dir) const
{
    json j = get_json(task_file);
    std::shared_ptr<MeshWrappers::Mesh> mesh = create_mesh(j["mesh"]);
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

std::shared_ptr<MeshWrappers::Mesh> TaskFactory::create_mesh(const json &mesh_properties) const
{
    MeshType mesh_type = get_mesh_type(mesh_properties["type"].get<std::string>());
    unsigned int n_refines = mesh_properties["geometry"]["n_refines"].get<unsigned>();

    switch (mesh_type) {
        case MeshType::cube:
            return std::make_shared<MeshWrappers::CubeMesh>(mesh_properties["geometry"]["size"]
                                                                .get<double>(), n_refines);
        case MeshType::simple_shell:
            return std::make_shared<MeshWrappers::SimpleShellMesh>(
                mesh_properties["geometry"]["sizes"]["inner_radius"].get<double>(),
                mesh_properties["geometry"]["sizes"]["outer_radius"].get<double>(),
                mesh_properties["geometry"]["sizes"]["cylinder_length"].get<double>(),
                n_refines
            );
        case MeshType::invalid_type: AssertThrow(false, dealii::ExcNotImplemented());
    }
}

std::shared_ptr<Solvers::SolverBase>
TaskFactory::create_solver(const json &solver_properties,
                           std::shared_ptr<MeshWrappers::Mesh> mesh,
                           const std::string &output_dir) const
{
    ProblemType problem_type = get_problem_type(solver_properties["type"]);

    switch (problem_type) {
        case ProblemType::simple_heat: {
            Material::SimpleHeat heat(solver_properties["material"]["thermal_diffusivity"].get<double>());
            return std::make_shared<Solvers::HeatSolver>(mesh, heat, output_dir);
        }
        case ProblemType::simple_elasticity: {
            Material::SimpleElasticity elasticity(solver_properties["material"]["E"].get<double>(),
                                                  solver_properties["material"]["G"].get<double>());
            return std::make_shared<Solvers::ElasticitySolver>(mesh, elasticity, output_dir);
        }
        case ProblemType::invalid_type: AssertThrow(false, dealii::ExcNotImplemented());
    }
}

MeshType TaskFactory::get_mesh_type(const std::string &type) const
{
    if (type == "cube") {
        return MeshType::cube;
    }
    else if (type == "simple_shell") {
        return MeshType::simple_shell;
    }
    else {
        return MeshType::invalid_type;
    }
}

ProblemType TaskFactory::get_problem_type(const std::string &type) const
{
    if (type == "simple_heat") {
        return ProblemType::simple_heat;
    }
    else if (type == "simple_elasticity") {
        return ProblemType::simple_elasticity;
    }
    else {
        return ProblemType::invalid_type;
    }
}
