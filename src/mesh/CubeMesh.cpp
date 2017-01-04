#include "CubeMesh.hpp"
#include "MeshUtilities.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/manifold_lib.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>
#include <src/mesh_markers/PlaneMarker.hpp>

using namespace dealii;

CubeMesh::CubeMesh(double size,
                   unsigned int n_refines)
    :
    MeshBase(n_refines),
    size(size)
{
    create();
}

void CubeMesh::create_coarse_mesh()
{
    GridGenerator::hyper_cube(tria, -size / 2, size / 2);
}

void CubeMesh::apply_manifold_ids()
{
    static const dealii::FlatManifold<3> flate_manifold(Point<3>(0, 0, 0));
    tria.set_manifold(0, flate_manifold);
    tria.set_all_manifold_ids(0);
}
void CubeMesh::apply_boundary_ids()
{
    PlaneMarker marker(1, Point<3>(0, 0, size / 2), 2);
    marker.mark_mesh(tria);
}

