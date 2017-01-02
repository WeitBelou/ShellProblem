#include "TaskFactory.hpp"
#include "MeshFactory.hpp"

#include "src/mesh/SimpleShellMesh.hpp"
#include "src/mesh/CubeMesh.hpp"

std::shared_ptr<MeshBase> MeshFactory::create_simple_shell_mesh(const json &geometry)
{
    const json sizes = geometry["sizes"];
    return std::make_shared<SimpleShellMesh>(
        sizes["inner_radius"].get<double>(),
        sizes["outer_radius"].get<double>(),
        sizes["cylinder_length"].get<double>(),
        geometry["n_refines"].get<unsigned>()
    );
}
std::shared_ptr<MeshBase> MeshFactory::create_cube_mesh(const json &geometry)
{
    return std::make_shared<CubeMesh>(
        geometry["size"].get<double>(),
        geometry["n_refines"].get<unsigned>());
}
std::shared_ptr<MeshBase> MeshFactory::create_mesh(const json &mesh_properties)
{
    std::__cxx11::string mesh_type = mesh_properties["type"].get<std::__cxx11::string>();

    const json geometry = mesh_properties["geometry"];

    if (mesh_type == "cube") {
        return create_cube_mesh(geometry);
    }
    else if (mesh_type == "simple_shell") {
        return create_simple_shell_mesh(geometry);
    }
    else {
        AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented());
        return nullptr;
    }
}