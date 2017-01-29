#include <deal.II/grid/grid_generator.h>
#include "IceIslandWithLegsMesh.hpp"
IceIslandWithLegsMesh::IceIslandWithLegsMesh(unsigned int n_global_refinements,
                                             const MeshMarkersGroup &markers,
                                             const double a,
                                             const double h)
    :
    GeneratedMesh(n_global_refinements, markers),
    a(a), h(h)
{
    create();
}

void IceIslandWithLegsMesh::create_coarse_mesh()
{
    dealii::Triangulation<3> cube;
    dealii::GridGenerator::subdivided_hyper_cube(cube, 3, 0, a);

    dealii::Triangulation<3> leg;
    dealii::GridGenerator::hyper_rectangle(leg,
                                           dealii::Point<3>(a / 3, a / 3, a),
                                           dealii::Point<3>(2 * a / 3, 2 * a / 3, a + h));

    dealii::GridGenerator::merge_triangulations(cube, leg, tria);
}

void IceIslandWithLegsMesh::apply_manifold_ids()
{

}
