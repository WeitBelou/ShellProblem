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

TEST(MaterialMarkersIslandTest, SingleMaterial)
{
    const double a = 10;
    const double h = 3;
    const unsigned axis = 2;

    std::vector<types::material_id> ids = {1};

    MeshMarkersGroup markers;
    markers.add_marker(std::make_shared<const TwoPlanesMarker>(ids[0], Point<3>(0, 0, 0),
                                                               Point<3>(0, 0, a + h), axis));
    MshMesh mesh("meshes/ice_island_with_legs.msh", markers);

    const Triangulation<3> &tria = mesh.mesh();
    for (auto cell: tria.active_cell_iterators()) {
        const types::material_id id = cell->material_id();
        ASSERT_TRUE(id == ids[0]) << std::string("id: ") + std::to_string(id);
    }
}

TEST(MaterialMarkersIslandTest, TwoMaterials)
{
    const double a = 10;
    const double h = 3;
    const unsigned axis = 2;

    std::vector<types::material_id> ids = {1, 2};

    MeshMarkersGroup markers;
    markers.add_marker(std::make_shared<const TwoPlanesMarker>(ids[0], Point<3>(0, 0, 0),
                                                               Point<3>(0, 0, a), axis));
    markers.add_marker(std::make_shared<const TwoPlanesMarker>(ids[1], Point<3>(0, 0, a),
                                                               Point<3>(0, 0, a + h), axis));
    MshMesh mesh("meshes/ice_island_with_legs.msh", markers);

    const Triangulation<3> &tria = mesh.mesh();
    for (auto cell: tria.active_cell_iterators()) {
        const types::material_id id = cell->material_id();
        ASSERT_TRUE(id == ids[0] || id == ids[1]) << std::string("id: ") + std::to_string(id);
    }
}

TEST(BoundaryMarkersIslandTest, Plane)
{
    const double a = 10;
    const double h = 3;
    const double r = 1;
    const double R = 2;
    const unsigned x_axis = 0;
    const unsigned y_axis = 1;
    const unsigned z_axis = 2;

    std::vector<types::boundary_id> ids = {1, 2};

    MeshMarkersGroup markers;
    markers.add_marker(std::make_shared<const PlaneMarker>(ids[0], Point<3>(0, 0, 0), z_axis));
    markers.add_marker(std::make_shared<const PlaneMarker>(ids[1], Point<3>(0, 0, a + h), z_axis));
    MshMesh mesh("meshes/ice_island_with_legs.msh", markers);

    const Triangulation<3> &tria = mesh.mesh();
    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                const Triangulation<3>::active_face_iterator face = cell->face(f);
                const types::boundary_id id = face->boundary_id();
                switch (id) {
                    case 0:
                        break;
                    case 1:
                        ASSERT_TRUE(MeshUtilities::is_face_on_plane(face, Point<3>(0, 0, 0), z_axis));
                        break;
                    case 2:
                        ASSERT_TRUE(MeshUtilities::is_face_on_plane(face, Point<3>(0, 0, a + h), z_axis));
                        break;
                    default:
                        ASSERT_TRUE(false) << std::string("Wrong id ") + std::to_string(id);
                }
            }
        }
    }
}