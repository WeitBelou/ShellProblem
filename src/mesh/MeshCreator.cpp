#include "MeshCreator.hpp"
#include "Utilities.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/tria_boundary_lib.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_reordering.h>
#include <deal.II/grid/grid_out.h>

#include <fstream>

using namespace MeshCreators;
using namespace Utilities;
using namespace dealii;

void MeshCreators::write_msh(const Triangulation<3, 3> &tria,
                             const std::string &output_file)
{
    GridOut grid_out;
    GridOutFlags::Msh msh_flags(true, true);
    grid_out.set_flags(msh_flags);

    std::ofstream out(output_file);
    grid_out.write_msh(tria, out);
}

void MeshCreators::write_vtu(const dealii::Triangulation<3> &tria, const std::string &output_file)
{
    GridOut grid_out;
    GridOutFlags::Vtu vtu_flags;
    grid_out.set_flags(vtu_flags);

    std::ofstream out(output_file);
    grid_out.write_vtu(tria, out);
}

void MeshCreators::read_from_msh(Triangulation<3> &tria, const std::string &input_file)
{
    GridIn<3> grid_in;
    grid_in.attach_triangulation(tria);

    std::ifstream in(input_file);
    grid_in.read_msh(in);
}

void MeshCreators::create_coarse_shell_mesh(dealii::Triangulation<3> &tria,
                                            const TaskReader::GeometryProperties &geometry)
{
    const double inner_radius = geometry.inner_radius;
    const double outer_radius = geometry.outer_radius;
    const double cylinder_length = geometry.cylinder_length;
    const double d = outer_radius - inner_radius;

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
    auto shell_to_cylinder = [](const Point<3> &p)
    {
        Point<3> result = p;
        return result;
    };
    GridTools::transform(shell_to_cylinder, shell_cylinder);

    //Merge
    GridGenerator::merge_triangulations(fairing, shell_cylinder, tria);
    GridTools::rotate(-numbers::PI_2, 1, tria);

    //Manifolds and boundaries
    static const SphericalManifold<3> spherical_manifold(fairing_center);
    static const CylindricalManifold<3> cylindrical_manifold(2);
    static const FlatManifold<3> flat_manifold;

    //Manifolds
    tria.set_manifold(0, flat_manifold);
    tria.set_manifold(1, spherical_manifold);
    tria.set_manifold(2, cylindrical_manifold);

    tria.set_all_manifold_ids(0);

    //Manifold and boundaries
    for (auto cell : tria.active_cell_iterators())
    {
        //Set manifold
        if (cell->center()(2) > 0)
        {
            cell->set_all_manifold_ids(1);
        }
        else
        {
            cell->set_all_manifold_ids(2);
        }

        //Set boundary ids
        for (size_t f = 0; f < GeometryInfo<3>::faces_per_cell; ++f)
        {
            if (cell->face(f)->at_boundary())
            {
                Triangulation<3>::face_iterator face = cell->face(f);
                if (is_face_on_sphere(face, fairing_center, outer_radius))
                {
                    face->set_boundary_id(2);
                }
            }
        }
    }
}

