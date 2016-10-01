#include "MeshWrappers.hpp"
#include "Utilities.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/manifold_lib.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

#include <fstream>

using namespace MeshWrappers;
using namespace Utilities;
using namespace dealii;

SimpleShellMesh::SimpleShellMesh(const Geometry::SimpleGeometry &geometry) :
    inner_radius(geometry.inner_radius),
    outer_radius(geometry.outer_radius),
    thickness(outer_radius - inner_radius),
    cylinder_length(geometry.cylinder_length),
    n_refinements(geometry.n_global_refinements)
{
    create_coarse_mesh();
    apply_manifold_ids();
    apply_boundary_ids();

    refine_mesh(n_refinements);
}

void SimpleShellMesh::create_coarse_mesh()
{
    //Fairing
    Triangulation<3> fairing;
    const Point<3> fairing_center;
    GridGenerator::half_hyper_shell(fairing, fairing_center,
                                    inner_radius, outer_radius);

    //Shell cylinder
    Triangulation<3> shell_cylinder;
    GridGenerator::half_hyper_shell(shell_cylinder, fairing_center,
                                    inner_radius, outer_radius);
    GridTools::rotate(numbers::PI, 1, shell_cylinder);
    auto shell_to_cylinder = [fairing_center, this](const Point<3> &p)
    {
        Point<3> result = p;

        if (p(0) < -1e-10)
        {
            if (is_point_on_sphere(p, fairing_center, inner_radius))
            {
                const double a = inner_radius / std::sqrt(2);
                result(0) = -cylinder_length + thickness;

                result(1) = (p(1) < 0) ? (-a) : (a);
                result(2) = (p(2) < 0) ? (-a) : (a);
            }
            else if (is_point_on_sphere(p, fairing_center, outer_radius))
            {
                const double a = outer_radius / std::sqrt(2);
                result(0) = -cylinder_length;

                result(1) = (p(1) < 0) ? (-a) : (a);
                result(2) = (p(2) < 0) ? (-a) : (a);
            }
        }

        return result;
    };
    GridTools::transform(shell_to_cylinder, shell_cylinder);

    //Merge
    GridGenerator::merge_triangulations(fairing, shell_cylinder, tria);
    GridTools::rotate(-numbers::PI_2, 1, tria);
}

void SimpleShellMesh::apply_manifold_ids()
{
    static const dealii::FlatManifold<3> flat_manifold;
    static const dealii::SphericalManifold<3> spherical_manifold(Point<3>(0, 0, 0));
    static const dealii::CylindricalManifold<3> cylindrical_manifold(2);

    tria.set_manifold(0, flat_manifold);
    tria.set_manifold(1, spherical_manifold);
    tria.set_manifold(2, cylindrical_manifold);

    tria.set_all_manifold_ids(0);

    for (auto cell : tria.active_cell_iterators())
    {
        if (cell->center()(2) > 0)
        {
            cell->set_all_manifold_ids(1);
        }
        else
        {
            cell->set_all_manifold_ids(2);
        }
    }
}

void SimpleShellMesh::apply_boundary_ids()
{
    for (auto cell : tria.active_cell_iterators())
    {
        for (size_t f = 0; f < GeometryInfo<3>::faces_per_cell; ++f)
        {
            if (cell->face(f)->at_boundary())
            {
                Triangulation<3>::face_iterator face = cell->face(f);
                if (is_face_on_sphere(face, Point<3>(0, 0, 0), outer_radius))
                {
                    face->set_all_boundary_ids(2);
                }
                else
                {
                    face->set_all_boundary_ids(1);
                }
            }
        }
    }
}

const dealii::Triangulation<3, 3> &Mesh::mesh() const
{
    return tria;
}

void Mesh::write_msh(const std::string &output_file)
{
    GridOut grid_out;
    GridOutFlags::Msh msh_flags(true, true);
    grid_out.set_flags(msh_flags);

    std::ofstream out(output_file);
    grid_out.write_msh(tria, out);
}

void Mesh::refine_mesh(size_t n_refines)
{
    tria.refine_global(n_refines);
}
