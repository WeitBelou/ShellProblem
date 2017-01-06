#ifndef SHELL_PROBLEM_MESH_FACTORY_HPP
#define SHELL_PROBLEM_MESH_FACTORY_HPP


#include <memory>
#include <deal.II/lac/solver_gmres.h>
#include <src/mesh_markers/MeshMarkersGroup.hpp>
#include "src/mesh/MeshBase.hpp"
#include "src/util/JsonUtil.hpp"

class MeshFactory
{

public:
    static std::shared_ptr<MeshBase> create_mesh(const json &mesh_properties,
                                                 const MeshMarkersGroup &markers);
private:
    static std::shared_ptr<MeshBase> create_cube_mesh(const json geometry, const MeshMarkersGroup &markers);
    static std::shared_ptr<MeshBase> create_simple_shell_mesh(const json geometry, const MeshMarkersGroup &markers);
    static std::shared_ptr<MeshBase> create_simple_ice_island(const json geometry, const MeshMarkersGroup &markers);
};


#endif //SHELL_PROBLEM_MESH_FACTORY_HPP
