#include <src/mesh_markers/CircleMarker.hpp>
#include "MeshFactory.hpp"

#include "src/mesh/SimpleShellMesh.hpp"
#include "src/mesh/CubeMesh.hpp"

std::shared_ptr<MeshBase> MeshFactory::create_mesh(const json &mesh_properties,
                                                   const MeshMarkersGroup &markers)
{
    MeshType mesh_type = get_type(mesh_properties["type"]);
    const json geometry = mesh_properties["geometry"];

    switch (mesh_type) {
        case MeshType::Cube:
            return create_cube_mesh(geometry, markers);
        case MeshType::SimpleShell:
            return create_simple_shell_mesh(geometry, markers);
        case MeshType::SimpleIceIsland:
            return create_simple_ice_island(geometry, markers);
    }
}
MeshFactory::MeshType MeshFactory::get_type(const json &type)
{
    const std::string type_string = type.get<std::string>();
    if (type_string == "cube") {
        return MeshType::Cube;
    }
    else if (type_string == "simple_shell") {
        return MeshType::SimpleShell;
    }
    else if (type_string == "simple_ice_island") {
        return MeshType::SimpleIceIsland;
    }
    else {
        AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented(
            std::string("Mesh type " + type_string + " doesn\'t exist.")
        ));
    };
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
