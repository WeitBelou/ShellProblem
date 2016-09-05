#include "MeshCreator.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

#include <fstream>
#include <cmath>
#include <math.h>

using namespace MeshCreators;
using namespace dealii;

void MeshCreators::create_shell_mesh(dealii::Triangulation<3> &tria, const TaskReader::GeometryProperties &geometry)
{
    const double L = geometry.L;
    const double r = geometry.r;
    const double d = geometry.d;

    const int n_global_refinements = geometry.n_global_refinements;

    Triangulation<3> head;
    GridGenerator::half_hyper_shell(head, Point<3>(0, 0, 0), r, r + d);

    Triangulation<3> tail;
    GridGenerator::cylinder_shell(tail, L, r, r + d, 4, 3);
    GridTools::rotate(M_PI / 2, 1, tail);
    GridTools::rotate(M_PI / 4, 0, tail);
    Tensor<1, 3> shift;
    shift[0] = -L;
    GridTools::shift(shift, tail);

    Triangulation<3> cap;
    const double a = r / std::sqrt(2);
    GridGenerator::hyper_rectangle(cap, Point<3>(-L + d, a, a), Point<3>(-L, -a, -a));

    Triangulation<3> tail_with_cap;
    GridGenerator::merge_triangulations(tail, cap, tail_with_cap);
    GridGenerator::merge_triangulations(head, tail_with_cap, tria);

    const static SphericalManifold<3> spherical_manifold;
    const static CylindricalManifold<3> cylindrical_manifold;

    tria.set_manifold(0, cylindrical_manifold);
    tria.set_manifold(1, spherical_manifold);
    tria.set_all_manifold_ids(0);

    for (auto cell : tria.active_cell_iterators())
    {
        const Point<3> cell_center = cell->center();
        if (cell_center[0] > 0)
        {
            cell->set_all_manifold_ids(1);
        }
    }

    for (auto cell : tria.active_cell_iterators())
    {
        if (cell->manifold_id() == 1)
        {
            for (size_t f = 0; f < GeometryInfo<3>::faces_per_cell; ++f)
            {
                if (cell->face(f)->at_boundary())
                {
                    const Point<3> face_center = cell->face(f)->center(true);
                    if (face_center.norm_square() > (r + d / 2) * (r + d / 2))
                    {
                        cell->face(f)->set_all_boundary_ids(1);
                    }
                }
            }
        }
    }

    tria.refine_global(n_global_refinements);
}

void MeshCreators::write_mesh(const Triangulation<3, 3> &tria,
                              const std::string &output_file)
{
    GridOut grid_out;
    GridOutFlags::Msh msh_flags(true, true);
    grid_out.set_flags(msh_flags);

    std::ofstream out(output_file);
    grid_out.write_msh(tria, out);
}

void MeshCreators::read_from_msh(Triangulation<3> &tria, const std::string &input_file)
{
    GridIn<3> grid_in;
    grid_in.attach_triangulation(tria);

    std::ifstream in(input_file);
    grid_in.read_msh(in);
}
