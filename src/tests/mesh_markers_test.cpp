#include <src/shell/mesh/MshMesh.hpp>
#include <src/shell/util/MeshUtilities.hpp>
#include "shell/mesh/CubeMesh.hpp"
#include "shell/mesh_markers/TwoPlanesMarker.hpp"
#include "shell/mesh_markers/PlaneMarker.hpp"
#include "gtest/gtest.h"

using namespace dealii;

TEST(MaterialMarkersCubeTest, SingleMaterial)
{
    const double size = 1.0;
    const Point<3> center(0, 0, 0);
    const int n_refines = 3;

    MeshMarkersGroup markers;
    const types::material_id id = 1;
    const unsigned axis = 2;
    markers.add_marker(std::make_shared<const TwoPlanesMarker>(id, Point<3>(0, 0, -size / 2),
                                                               Point<3>(0, 0, size / 2), axis));
    CubeMesh mesh(size, center, n_refines, markers);

    const Triangulation<3> &tria = mesh.mesh();
    for (auto cell: tria.active_cell_iterators()) {
        ASSERT_EQ(cell->material_id(), id);
    }
}

TEST(MaterialMarkersCubeTest, TwoMaterials)
{
    const double size = 1.0;
    const Point<3> center(0, 0, 0);
    const int n_refines = 3;

    MeshMarkersGroup markers;
    const std::vector<types::material_id> ids{1, 2};
    const unsigned axis = 2;

    markers.add_marker(std::make_shared<const TwoPlanesMarker>(ids[0], Point<3>(0, 0, -size / 2),
                                                               Point<3>(0, 0, 0), axis));
    markers.add_marker(std::make_shared<const TwoPlanesMarker>(ids[1], Point<3>(0, 0, 0),
                                                               Point<3>(0, 0, size / 2), axis));
    CubeMesh mesh(size, center, n_refines, markers);

    const Triangulation<3> &tria = mesh.mesh();
    for (auto cell: tria.active_cell_iterators()) {
        const types::material_id id = cell->material_id();
        ASSERT_TRUE(id == ids[0] || id == ids[1]) << std::string("id: ") + std::to_string(id);
    }
}