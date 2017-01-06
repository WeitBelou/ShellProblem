#include <src/mesh_markers/CircleMarker.hpp>
#include "MeshFactory.hpp"

#include "src/mesh/SimpleShellMesh.hpp"
#include "src/mesh/CubeMesh.hpp"

std::shared_ptr<MeshBase> MeshFactory::create_mesh(const json &mesh_properties,
                                                   const MeshMarkersGroup &markers)
{
    std::string mesh_type = mesh_properties["type"].get<std::string>();

    const json geometry = mesh_properties["geometry"];

    if (mesh_type == "cube") {
        return create_cube_mesh(geometry, markers);
    }
    else if (mesh_type == "simple_shell") {
        return create_simple_shell_mesh(geometry, markers);
    }
    else if (mesh_type == "simple_ice_island") {
        return create_simple_ice_island(geometry, markers);
    }
    else {
        AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented());
        return nullptr;
    }
}
std::shared_ptr<MeshBase> MeshFactory::create_simple_shell_mesh(const json geometry, const MeshMarkersGroup &markers)
{
    const json sizes = geometry["sizes"];

    const double inner_radius = sizes["inner_radius"].get<double>();
    const double outer_radius = sizes["outer_radius"].get<double>();
    const double cylinder_length = sizes["cylinder_length"].get<double>();
    const unsigned int n_refines = geometry["n_refines"].get<unsigned>();

    return std::make_shared<SimpleShellMesh>(
        inner_radius, outer_radius,
        cylinder_length, n_refines,
        markers
    );
}
std::shared_ptr<MeshBase> MeshFactory::create_cube_mesh(const json geometry, const MeshMarkersGroup &markers)
{
    const double size = geometry["size"].get<double>();
    const unsigned int n_refines = geometry["n_refines"].get<unsigned>();
    return std::make_shared<CubeMesh>(size, n_refines, markers);
}

std::shared_ptr<MeshBase> MeshFactory::create_simple_ice_island(const json geometry, const MeshMarkersGroup &markers)
{
    const double size = geometry["size"].get<double>();
    const unsigned int n_refines = geometry["n_refines"].get<unsigned>();
    return std::make_shared<CubeMesh>(size, n_refines, markers);
}
