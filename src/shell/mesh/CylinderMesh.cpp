#include "CylinderMesh.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/manifold_lib.h>
#include <src/shell/util/MeshUtilities.hpp>
#include <deal.II/grid/tria_boundary_lib.h>
CylinderMesh::CylinderMesh(const double radius,
                           const double height,
                           const dealii::Point<3> &center,
                           unsigned int n_global_refinements)
    :
    GeneratedMesh(n_global_refinements),
    radius(radius),
    height(height),
    center(center)
{
    create();
}

void CylinderMesh::create_coarse_mesh()
{
    dealii::GridGenerator::cylinder(tria, radius, height / 2);
    dealii::GridTools::rotate(dealii::numbers::PI_2, 1, tria);
    dealii::GridTools::shift(center, tria);
}

void CylinderMesh::apply_manifold_ids()
{
    static const dealii::CylindricalManifold<3> cylindrical_manifold(dealii::Point<3>(0, 0, 1), center);
    tria.set_manifold(0, cylindrical_manifold);
    tria.set_all_manifold_ids(0);
}

void CylinderMesh::apply_boundary_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            auto face = cell->face(f);
            if (face->at_boundary()) {
                if (MeshUtilities::is_face_on_plane(face, dealii::Point<3>(0, 0, height / 2) + center, 2)) {
                    face->set_all_boundary_ids(1);
                }
                else if (MeshUtilities::is_face_on_plane(face, dealii::Point<3>(0, 0, -height / 2) + center, 2)) {
                    face->set_all_boundary_ids(2);
                }
            }
        }
    }
}

void CylinderMesh::apply_material_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        cell->set_material_id(1);
    }
}

