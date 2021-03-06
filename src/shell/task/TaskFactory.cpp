#include "TaskFactory.hpp"

#include "src/shell/mesh/MeshFactory.hpp"
#include "src/shell/boundaries/BoundariesFactory.hpp"
#include "src/shell/linear_solver/LinearSolverFactory.hpp"
#include "src/shell/materials/MaterialFactory.hpp"
#include "src/shell/materials/MaterialsGroup.hpp"
#include "src/shell/solvers/SolverBuilder.hpp"

std::shared_ptr<Task> TaskFactory::create_task_from_json(json task, const std::string &output_dir)
{
    const json &mesh_properties = task["mesh"];
    std::shared_ptr<MeshBase> mesh = MeshFactory::create_mesh(mesh_properties);

    const json &linear_solver_properties = task["linear_solver"];
    std::shared_ptr<LinearSolverBase>
        linear_solver = LinearSolverFactory::create_linear_solver(linear_solver_properties);

    const json &boundaries_properties = task["boundaries"];
    BoundariesGroup boundaries = BoundariesFactory::create_boundaries(boundaries_properties);

    const json &materials_properties = task["materials"];
    MaterialsGroup materials = MaterialFactory::create_materials(materials_properties);

    const json &solver_properties = task["solver"];
    std::shared_ptr<SolverBase> solver = SolverBuilder::create_solver(solver_properties,
                                                                      mesh,
                                                                      linear_solver,
                                                                      boundaries,
                                                                      materials);

    return std::make_shared<Task>(solver, output_dir);
}

