#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/manifold_lib.h>
#include <src/shell/util/MeshUtilities.hpp>
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
    const double c = a / 11.0;

    static const dealii::FlatManifold<3> flat_manifold;
    const dealii::Point<3> &z_axis = dealii::Point<3>(0, 0, 1);
    static const dealii::CylindricalManifold<3> left_cylinder(z_axis,
                                                              dealii::Point<3>(3.5 * c, 5.5 * c, a));

    static const dealii::CylindricalManifold<3> right_cylinder(z_axis,
                                                               dealii::Point<3>(7.5 * c, 5.5 * c, a));

    static const dealii::CylindricalManifold<3> top_cylinder(z_axis,
                                                             dealii::Point<3>(5.5 * c, 7.5 * c, a));
    static const dealii::CylindricalManifold<3> bottom_cylinder(z_axis,
                                                                dealii::Point<3>(5.5 * c, 3.5 * c, a));

    tria.set_manifold(0, flat_manifold);
    tria.set_manifold(1, left_cylinder);
    tria.set_manifold(2, right_cylinder);
    tria.set_manifold(3, top_cylinder);
    tria.set_manifold(4, bottom_cylinder);

    tria.set_all_manifold_ids(0);
    for (auto cell : tria.active_cell_iterators()) {
        const dealii::Point<3> center = cell->center();
        if (center(2) > a) {
            if (MeshUtilities::fuzzy_equal(center(1), 5.5 * c)) {
                if (center(0) < a / 2) {
                    cell->set_all_manifold_ids(1);
                }
                else {
                    cell->set_all_manifold_ids(2);
                }
            }
            else {
                if (center(1) > a / 2) {
                    cell->set_all_manifold_ids(3);
                }
                else {
                    cell->set_all_manifold_ids(4);
                }
            }
        }
    }
}
