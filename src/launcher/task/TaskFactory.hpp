#ifndef SHELL_PROBLEM_TASK_FACTORY_HPP
#define SHELL_PROBLEM_TASK_FACTORY_HPP

#include <memory>
#include <src/third_party/json.hpp>
#include <deal.II/bundled/boost/concept_check.hpp>
#include "Task.hpp"

using json = nlohmann::json;

enum class ProblemType
{
    simple_heat, simple_elasticity, invalid_type
};

enum class MeshType
{
    simple_shell, cube, invalid_type
};

class TaskFactory
{
public:
    TaskFactory() = default;

    std::shared_ptr<Task> create_task(const std::string &task_file, const std::string &output_dir) const;

private:
    nlohmann::basic_json<> get_json(const std::string &task_file) const;

    std::shared_ptr<MeshWrappers::Mesh> create_mesh(const json &mesh_properties) const;
    std::shared_ptr<Solvers::SolverBase>
    create_solver(const json &solver_properties,
                  std::shared_ptr<MeshWrappers::Mesh> mesh,
                  const std::string &output_dir) const;

    MeshType get_mesh_type(const std::string &type) const;
    ProblemType get_problem_type(const std::string &type) const;
};


#endif //SHELL_PROBLEM_TASK_FACTORY_HPP
