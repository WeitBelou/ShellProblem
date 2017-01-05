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
                                 unsigned int n_refines,
                                 std::shared_ptr<MeshMarkerBase> marker)
    :
    MeshBase(n_refines, marker),
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
    GridTools::rotate(-numbers::PI_2, 1, fairing);

    //Shell cylinder
    dealii::Triangulation<3> shell_cylinder;
    GridGenerator::cylinder_shell(shell_cylinder, cylinder_length,
                                  inner_radius, outer_radius,
                                  4, 4);
    GridTools::rotate(numbers::PI, 1, shell_cylinder);
    GridTools::rotate(numbers::PI_4, 2, shell_cylinder);

    //Merge
    GridGenerator::merge_triangulations(fairing, shell_cylinder, tria);
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