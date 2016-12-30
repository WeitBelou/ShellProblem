#ifndef SHELL_PROBLEM_TASK_FACTORY_HPP
#define SHELL_PROBLEM_TASK_FACTORY_HPP

#include <memory>
#include "Task.hpp"
#include "TaskUtil.hpp"
#include "src/mesh/MeshBase.hpp"

class TaskFactory
{
public:
    TaskFactory(const std::string &output_dir);

    std::shared_ptr<Task> create_task_from_json(json task) const;

private:
    const std::string output_dir;

    std::shared_ptr<Meshes::MeshBase> create_mesh(const json &mesh_properties) const;
    std::shared_ptr<Solvers::SolverBase>
    create_solver(const json &solver_properties, std::shared_ptr<Meshes::MeshBase> mesh) const;
};


#endif //SHELL_PROBLEM_TASK_FACTORY_HPP
