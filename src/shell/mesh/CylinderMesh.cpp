#include "CylinderMesh.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/manifold_lib.h>
#include <src/shell/util/MeshUtilities.hpp>
CylinderMesh::CylinderMesh(const double radius,
                           const double height,
                           const dealii::Point<3> &center,
                           unsigned int n_global_refinements,
                           const MeshMarkersGroup &markers)
    :
    GeneratedMesh(n_global_refinements, markers),
    radius(radius),
    height(height),
    center(center)
{
    create();
}

void CylinderMesh::create_coarse_mesh()
{
    const double a = radius / sqrt(2);
    dealii::Point<3> left_bottom(-a, -a, -height / 2);
    dealii::Point<3> right_top(a, a, height / 2);

    dealii::GridGenerator::hyper_rectangle(tria, left_bottom, right_top);
    dealii::GridTools::shift(center, tria);
}

void CylinderMesh::apply_manifold_ids()
{
    static const dealii::CylindricalManifold<3> cylindrical_manifold(2);
    static const dealii::FlatManifold<3> flat_manifold;
    tria.set_manifold(0, flat_manifold);
    tria.set_manifold(1, cylindrical_manifold);

    tria.set_all_manifold_ids(0);
    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            auto face = cell->face(f);
            if (face->at_boundary() && MeshUtilities::fuzzy_equal(face->center()(2), 0) ) {
                face->set_all_manifold_ids(1);
            }
        }
    }
}

