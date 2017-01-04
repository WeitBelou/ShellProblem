#ifndef SHELL_PROBLEM_TASK_FACTORY_HPP
#define SHELL_PROBLEM_TASK_FACTORY_HPP

#include <memory>
#include <deal.II/lac/solver_gmres.h>
#include <src/linear_solver/LinearSolverBase.hpp>
#include "Task.hpp"
#include "TaskUtil.hpp"
#include "src/mesh/MeshBase.hpp"

class TaskFactory
{
public:
    static std::shared_ptr<Task> create_task_from_json(json task, const std::string &output_dir);

private:

    static std::shared_ptr<SolverBase>
    create_solver(const json &solver_properties,
                     std::shared_ptr<MeshBase> mesh,
                     std::shared_ptr<LinearSolverBase> linear_solver);
};


#endif //SHELL_PROBLEM_TASK_FACTORY_HPP
