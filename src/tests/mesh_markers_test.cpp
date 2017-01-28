#include "shell/mesh/CubeMesh.hpp"
#include "shell/mesh_markers/TwoPlanesMarker.hpp"
#include "gtest/gtest.h"
TEST(MaterialMarkersCubeTest, SingleMaterial)
{
    MeshMarkersGroup markers;
    markers.add_marker(std::make_shared<const TwoPlanesMarker>(1, dealii::Point<3>(0, 0, -0.5),
                                                               dealii::Point<3>(0, 0, 0.5), 2));
    CubeMesh mesh(1.0, dealii::Point<3>(0, 0, 0), 0, markers);

    auto tria = mesh.mesh();
    for (auto cell: tria.active_cell_iterators()) {
        ASSERT_EQ(cell->material_id(), 1);
    }
}
