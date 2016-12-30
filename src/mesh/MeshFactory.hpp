#ifndef SHELL_PROBLEM_MESH_FACTORY_HPP
#define SHELL_PROBLEM_MESH_FACTORY_HPP


#include <memory>
#include "src/mesh/MeshBase.hpp"
#include "src/launcher/task/TaskUtil.hpp"

class MeshFactory
{

public:
    static std::shared_ptr<Meshes::MeshBase> create_cube_mesh(const json &geometry);
    static std::shared_ptr<Meshes::MeshBase> create_simple_shell_mesh(const json &geometry);
};


#endif //SHELL_PROBLEM_MESH_FACTORY_HPP
