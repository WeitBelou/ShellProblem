#include "CubeMesh.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/manifold_lib.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>
#include <src/shell/util/MeshUtilities.hpp>

using namespace dealii;

CubeMesh::CubeMesh(const double size, const Point<3> &center, unsigned int n_refines)
    :
    GeneratedMesh(n_refines),
    size(size),
    center(center)
{
    create();
}

void CubeMesh::create_coarse_mesh()
{
    GridGenerator::hyper_cube(tria, -size / 2, size / 2);
    GridTools::shift(center, tria);
}

void CubeMesh::apply_manifold_ids()
{
    static const dealii::FlatManifold<3> flat_manifold(Point<3>(0, 0, 0));
    tria.set_manifold(0, flat_manifold);
    tria.set_all_manifold_ids(0);
}

void CubeMesh::apply_boundary_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < GeometryInfo<3>::faces_per_cell; ++f) {
            auto face = cell->face(f);
            if (face->at_boundary()) {
                if (MeshUtilities::is_face_on_plane(face, dealii::Point<3>(0, 0, size / 2) + center, 2)) {
                    face->set_all_boundary_ids(1);
                }
                else if (dealii::Point<3>(0, 0, -size / 2) + center, 2) {
                    face->set_all_boundary_ids(2);
                }
            }
        }
    }
}

void CubeMesh::apply_material_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        cell->set_material_id(1);
    }
}
