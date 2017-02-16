#pragma once
#include <memory>

#include <deal.II/lac/solver_gmres.h>
#include "MeshBase.hpp"
#include "src/shell/util/JsonUtil.hpp"

class MeshFactory
{

public:
    static std::shared_ptr<MeshBase> create_mesh(const json &mesh_properties);
private:
    static std::shared_ptr<MeshBase> create_cube_mesh(const json geometry);
    static std::shared_ptr<MeshBase> create_simple_shell_mesh(const json geometry);
    static std::shared_ptr<MeshBase> create_cylinder_mesh(const json &geometry);
    static std::shared_ptr<MeshBase> create_simple_island_mesh(const json &geometry);
    static std::shared_ptr<MeshBase> create_layered_island_mesh(const json &geometry);
    static std::shared_ptr<MeshBase> create_island_with_well(const json &geometry);
};
