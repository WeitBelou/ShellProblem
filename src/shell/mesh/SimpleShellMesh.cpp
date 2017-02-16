#include "SimpleShellMesh.hpp"

#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/manifold.h>
#include <deal.II/grid/manifold_lib.h>

using namespace dealii;

SimpleShellMesh::SimpleShellMesh(double inner_radius,
                                 double outer_radius,
                                 double cylinder_length,
                                 unsigned int n_refines)
    :
    GeneratedMesh(n_refines),
    inner_radius(inner_radius),
    outer_radius(outer_radius),
    thickness(outer_radius - inner_radius),
    cylinder_length(cylinder_length)
{
    create();
}
void SimpleShellMesh::create_coarse_mesh()
{
    //Fairing
    Triangulation<3> fairing;
    const Point<3> fairing_center(0, 0, 0);
    GridGenerator::half_hyper_shell(fairing, fairing_center,
                                    inner_radius, outer_radius);
    GridTools::rotate(-numbers::PI_2, 1, fairing);

    //Shell cylinder
    Triangulation<3> shell_cylinder;
    GridGenerator::cylinder_shell(shell_cylinder, cylinder_length,
                                  inner_radius, outer_radius,
                                  4, 4);
    GridTools::rotate(numbers::PI, 1, shell_cylinder);
    GridTools::rotate(numbers::PI_4, 2, shell_cylinder);

    GridGenerator::merge_triangulations(fairing, shell_cylinder, tria);

    //Cap
    Triangulation<3> cap;
    const double a = outer_radius / sqrt(2);
    GridGenerator::hyper_rectangle(cap, Point<3>(-a, -a, -(cylinder_length + thickness)),
                                   Point<3>(a, a, -cylinder_length));

    GridGenerator::merge_triangulations(tria, cap, tria);
}
void SimpleShellMesh::apply_manifold_ids()
{
    static const dealii::FlatManifold<3> flat_manifold;
    static const dealii::SphericalManifold<3> spherical_manifold(dealii::Point<3>(0, 0, 0));
    static const dealii::CylindricalManifold<3> cylindrical_manifold(2);

    tria.set_manifold(0, flat_manifold);
    tria.set_manifold(1, spherical_manifold);
    tria.set_manifold(2, cylindrical_manifold);

    tria.set_all_manifold_ids(0);

    for (auto cell : tria.active_cell_iterators()) {
        if (cell->center()(2) > 0) {
            cell->set_all_manifold_ids(1);
        }
        else {
            cell->set_all_manifold_ids(2);
        }
    }
}

void SimpleShellMesh::apply_boundary_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            auto face = cell->face(f);
            if (face->at_boundary()) {
                face->set_all_boundary_ids(0);
            }
        }
    }
}

void SimpleShellMesh::apply_material_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        cell->set_material_id(0);
    }
}
