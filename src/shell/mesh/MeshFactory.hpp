#pragma once
#include <memory>

#include <deal.II/lac/solver_gmres.h>
#include "src/shell/mesh_markers/MeshMarkersGroup.hpp"
#include "MeshBase.hpp"
#include "src/shell/util/JsonUtil.hpp"

class MeshFactory
{

public:
    static std::shared_ptr<MeshBase> create_mesh(const json &mesh_properties,
                                                 const MeshMarkersGroup &markers);
private:
    static std::shared_ptr<MeshBase> create_cube_mesh(const json geometry, const MeshMarkersGroup &markers);
    static std::shared_ptr<MeshBase> create_simple_shell_mesh(const json geometry, const MeshMarkersGroup &markers);
    static std::shared_ptr<MeshBase> create_simple_ice_island(const json geometry, const MeshMarkersGroup &markers);
    static std::shared_ptr<MeshBase> create_mesh_from_msh_file(const json &geometry, const MeshMarkersGroup &markers);
};
