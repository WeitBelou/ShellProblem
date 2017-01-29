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
    const unsigned n = 11;
    const double c = a / 11.0;
    dealii::GridGenerator::subdivided_hyper_cube(cube, n, 0, a);

    dealii::Triangulation<3> leg;
    dealii::GridGenerator::hyper_rectangle(leg,
                                           dealii::Point<3>(3 * c, 5 * c, a),
                                           dealii::Point<3>(4 * c, 6 * c, a + h));
    dealii::GridGenerator::merge_triangulations(cube, leg, tria);
    leg.clear();

    dealii::GridGenerator::hyper_rectangle(leg,
                                           dealii::Point<3>(7 * c, 5 * c, a),
                                           dealii::Point<3>(8 * c, 6 * c, a + h));
    dealii::GridGenerator::merge_triangulations(tria, leg, tria);
    leg.clear();

    dealii::GridGenerator::hyper_rectangle(leg,
                                           dealii::Point<3>(5 * c, 7 * c, a),
                                           dealii::Point<3>(6 * c, 8 * c, a + h));
    dealii::GridGenerator::merge_triangulations(tria, leg, tria);
    leg.clear();

    dealii::GridGenerator::hyper_rectangle(leg,
                                           dealii::Point<3>(5 * c, 3 * c, a),
                                           dealii::Point<3>(6 * c, 4 * c, a + h));
    dealii::GridGenerator::merge_triangulations(tria, leg, tria);
    leg.clear();
}

void IceIslandWithLegsMesh::apply_manifold_ids()
{

}
