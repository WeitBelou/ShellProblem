#include "CylinderMesh.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/manifold_lib.h>
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
    dealii::GridGenerator::cylinder(tria, radius, height / 2);
    dealii::GridTools::shift(center, tria);
    dealii::GridTools::rotate(-dealii::numbers::PI_2, 1, tria);
}

void CylinderMesh::apply_manifold_ids()
{
    static const dealii::CylindricalManifold<3> cylindrical_manifold(2);
    tria.set_manifold(0, cylindrical_manifold);
    tria.set_all_manifold_ids(0);
}

