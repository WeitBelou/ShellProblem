#include "MeshFactory.hpp"

#include "src/mesh/SimpleShellMesh.hpp"
#include "src/mesh/CubeMesh.hpp"

std::shared_ptr<Meshes::MeshBase> MeshFactory::create_simple_shell_mesh(const json &geometry)
{
    const json sizes = geometry["sizes"];
    return std::make_shared<Meshes::SimpleShellMesh>(
        sizes["inner_radius"].get<double>(),
        sizes["outer_radius"].get<double>(),
        sizes["cylinder_length"].get<double>(),
        geometry["n_refines"].get<unsigned>()
    );
}
std::shared_ptr<Meshes::MeshBase> MeshFactory::create_cube_mesh(const json &geometry)
{
    return std::make_shared<Meshes::CubeMesh>(
        geometry["size"].get<double>(),
        geometry["n_refines"].get<unsigned>());
}