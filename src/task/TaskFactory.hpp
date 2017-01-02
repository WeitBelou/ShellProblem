#ifndef SHELL_PROBLEM_TASK_FACTORY_HPP
#define SHELL_PROBLEM_TASK_FACTORY_HPP

#include <memory>
#include <deal.II/lac/solver_gmres.h>
#include <src/boundaries/BoundariesMap.hpp>
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
    std::shared_ptr<SolverBase>
    create_solver(const json &solver_properties, std::shared_ptr<Meshes::MeshBase> mesh) const;
    dealii::SolverGMRES<>::AdditionalData get_gmres_additional_data(const json &linear_solver_properties) const;
    BoundariesMap create_boundaries(const json &solver_properties) const;
};


#endif //SHELL_PROBLEM_TASK_FACTORY_HPP
