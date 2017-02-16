#include "MeshFactory.hpp"

#include "SimpleShellMesh.hpp"
#include "CubeMesh.hpp"
#include "CylinderMesh.hpp"

std::shared_ptr<MeshBase> MeshFactory::create_mesh(const json &mesh_properties)
{
    const std::string mesh_type = mesh_properties["type"].get<std::string>();
    const json geometry = mesh_properties["geometry"];

    if (mesh_type == "cube") {
        return create_cube_mesh(geometry);
    }
    else if (mesh_type == "simple_shell") {
        return create_simple_shell_mesh(geometry);
    }
    else if (mesh_type == "cylinder") {
        return create_cylinder_mesh(geometry);
    }
    else {
        AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented(
            std::string("Mesh type " + mesh_type + " doesn\'t exist.")
        ));
        return nullptr;
    };
}

std::shared_ptr<MeshBase> MeshFactory::create_simple_shell_mesh(const json geometry)
{
    const json sizes = geometry["sizes"];

    const double inner_radius = sizes["inner_radius"].get<double>();
    const double outer_radius = sizes["outer_radius"].get<double>();
    const double cylinder_length = sizes["cylinder_length"].get<double>();
    const unsigned int n_refines = geometry["n_refines"].get<unsigned>();

    return std::make_shared<SimpleShellMesh>(
        inner_radius, outer_radius,
        cylinder_length, n_refines
    );
}

std::shared_ptr<MeshBase> MeshFactory::create_cube_mesh(const json geometry)
{
    const double size = geometry["size"].get<double>();
    const unsigned int n_refines = geometry["n_refines"].get<unsigned>();
    const dealii::Point<3> center = JsonUtil::get_point(geometry["center"]);
    return std::make_shared<CubeMesh>(size, center, n_refines);
}

std::shared_ptr<MeshBase> MeshFactory::create_cylinder_mesh(const json &geometry)
{
    const double radius = geometry["radius"].get<double>();
    const double height = geometry["height"].get<double>();
    const dealii::Point<3> center = JsonUtil::get_point(geometry["center"]);
    const unsigned n_refines = geometry["n_refines"].get<unsigned>();
    return std::make_shared<CylinderMesh>(radius, height, center, n_refines);
}
