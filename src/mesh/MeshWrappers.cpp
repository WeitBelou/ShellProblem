#include "MeshWrappers.hpp"
#include "MeshUtilities.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/manifold_lib.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

#include <fstream>

using namespace MeshWrappers;
using namespace MeshUtilities;
using namespace dealii;

void Mesh::initialize(const std::string &input)
{
    ParameterHandler prm;
    declare_parameters(prm);
    prm.parse_input(input);
    get_parameters(prm);

    create_coarse_mesh();
    apply_manifold_ids();
    apply_boundary_ids();

    refine_mesh(n_global_refinements);
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
                    face->set_all_boundary_ids(1);
                }
                else
                {
                    face->set_all_boundary_ids(0);
                }
            }
        }
    }
}

void SimpleShellMesh::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        prm.enter_subsection("Sizes");
        {
            prm.declare_entry("Inner radius", "5.0",
                              Patterns::Double(0),
                              "Inner radius of the shell");
            prm.declare_entry("Outer radius", "5.3",
                              Patterns::Double(0),
                              "Outer radius of the shell");
            prm.declare_entry("Cylinder length", "5.0",
                              Patterns::Double(0),
                              "Length of shell\'s cylindrical part");
        }
        prm.leave_subsection();

        prm.declare_entry("N global refinements", "0",
                          Patterns::Integer(0, 6),
                          "Number of initial global refinements");
    }
    prm.leave_subsection();
}

void SimpleShellMesh::get_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        prm.enter_subsection("Sizes");
        {
            inner_radius = prm.get_double("Inner radius");
            outer_radius = prm.get_double("Outer radius");
            thickness = outer_radius - inner_radius;

            cylinder_length = prm.get_double("Cylinder length");
        }
        prm.leave_subsection();

        n_global_refinements = prm.get_integer("N global refinements");
    }
    prm.leave_subsection();
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
    for (auto cell : tria.active_cell_iterators())
    {
        for (size_t f = 0; f < GeometryInfo<3>::faces_per_cell; ++f)
        {
            if (cell->face(f)->at_boundary())
            {
                Triangulation<3>::active_face_iterator face = cell->face(f);
                if (is_face_on_plane(face, Point<3>(0, 0, size / 2), 2))
                {
                    face->set_all_boundary_ids(1);
                }
                else
                {
                    face->set_all_boundary_ids(0);
                }
            }
        }
    }
}

void CubeMesh::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        prm.declare_entry("Size", "5.0",
                          Patterns::Double(0),
                          "Length of cube side");
        prm.declare_entry("N global refinements", "0",
                          Patterns::Integer(0, 6),
                          "Number of initial global refinements");
    }
    prm.leave_subsection();
}

void CubeMesh::get_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        size = prm.get_double("Size");
        n_global_refinements = prm.get_integer("N global refinements");
    }
    prm.leave_subsection();
}
