#include "CubeMesh.hpp"
#include "MeshUtilities.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/manifold_lib.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

using namespace Meshes;
using namespace MeshUtilities;
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
    for (auto cell : tria.active_cell_iterators()) {
        for (unsigned int f = 0; f < GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                Triangulation<3>::active_face_iterator face = cell->face(f);
                if (is_face_on_plane(face, Point<3>(0, 0, size / 2), 2)) {
                    face->set_all_boundary_ids(1);
                }
                else {
                    face->set_all_boundary_ids(0);
                }
            }
        }
    }
}

