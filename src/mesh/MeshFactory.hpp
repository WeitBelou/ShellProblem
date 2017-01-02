#ifndef SHELL_PROBLEM_MESH_FACTORY_HPP
#define SHELL_PROBLEM_MESH_FACTORY_HPP


#include <memory>
#include <deal.II/lac/solver_gmres.h>
#include "src/mesh/MeshBase.hpp"
#include "src/task/TaskUtil.hpp"

class MeshFactory
{

public:
    static std::shared_ptr<MeshBase> create_mesh(const json &mesh_properties);
private:
    static std::shared_ptr<MeshBase> create_simple_shell_mesh(const json &geometry);
    static std::shared_ptr<MeshBase> create_cube_mesh(const json &geometry);
};


#endif //SHELL_PROBLEM_MESH_FACTORY_HPP
