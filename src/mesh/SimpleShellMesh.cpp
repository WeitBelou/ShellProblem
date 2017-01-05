#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/manifold.h>
#include <deal.II/grid/manifold_lib.h>
#include <src/mesh_markers/SphereMarker.hpp>

#include "CubeMesh.hpp"
#include "SimpleShellMesh.hpp"
#include "MeshUtilities.hpp"

using namespace dealii;

SimpleShellMesh::SimpleShellMesh(double inner_radius,
                                 double outer_radius,
                                 double cylinder_length,
                                 unsigned int n_refines)
    :
    MeshBase(n_refines),
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
    dealii::Triangulation<3> fairing;
    const dealii::Point<3> fairing_center;
    GridGenerator::half_hyper_shell(fairing, fairing_center,
                                    inner_radius, outer_radius);

    //Shell cylinder
    dealii::Triangulation<3> shell_cylinder;
    GridGenerator::half_hyper_shell(shell_cylinder, fairing_center,
                                    inner_radius, outer_radius);
    dealii::GridTools::rotate(dealii::numbers::PI, 1, shell_cylinder);
    auto shell_to_cylinder = [fairing_center, this](const dealii::Point<3> &p)
    {
        dealii::Point<3> result = p;

        if (p(0) < 0) {
            if (MeshUtilities::is_point_on_sphere(p, fairing_center, inner_radius)) {
                const double a = inner_radius / std::sqrt(2);
                result(0) = -cylinder_length + thickness;

                result(1) = (p(1) < 0) ? (-a) : (a);
                result(2) = (p(2) < 0) ? (-a) : (a);
            }
            else if (MeshUtilities::is_point_on_sphere(p, fairing_center, outer_radius)) {
                const double a = outer_radius / std::sqrt(2);
                result(0) = -cylinder_length;

                result(1) = (p(1) < 0) ? (-a) : (a);
                result(2) = (p(2) < 0) ? (-a) : (a);
            }
        }

        return result;
    };
    dealii::GridTools::transform(shell_to_cylinder, shell_cylinder);

    //Merge
    GridGenerator::merge_triangulations(fairing, shell_cylinder, tria);
    dealii::GridTools::rotate(-dealii::numbers::PI_2, 1, tria);
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
    SphereMarker marker(1, Point<3>(0, 0, 0), outer_radius);
    marker.mark_mesh(tria);
}