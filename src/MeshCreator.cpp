#include "MeshCreator.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/opencascade/boundary_lib.h>
#include <deal.II/opencascade/utilities.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

#include <fstream>
#include <math.h>

using namespace MeshCreators;
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

void MeshCreators::read_from_msh(Triangulation<3> &tria, const std::string &input_file)
{
    GridIn<3> grid_in;
    grid_in.attach_triangulation(tria);

    std::ifstream in(input_file);
    grid_in.read_msh(in);
}

void ::MeshCreators::create_coarse_shell_mesh(dealii::Triangulation<3> &tria,
                                              const TaskReader::GeometryProperties &geometry)
{
    const double inner_radius = geometry.inner_radius;
    const double outer_radius = geometry.outer_radius;
    const double cylinder_length = geometry.cylinder_length;

    //Fairing
    Triangulation<3> fairing;
    const Point<3> fairing_center;
    GridGenerator::half_hyper_shell(fairing, fairing_center,
                                    inner_radius, outer_radius);

    //Shell cylinder
    Triangulation<3> shell_cylinder;
    GridGenerator::half_hyper_shell(shell_cylinder, fairing_center,
                                    inner_radius, outer_radius);
    GridTools::rotate(M_PI, 1, shell_cylinder);

    auto transform_function =
        [outer_radius, inner_radius, cylinder_length](const Point<3> &p)
        {
            Point<3> result = p;
            const double d = outer_radius - inner_radius;

            auto fuzzy_equal = [](double a, double b)
            {
                return std::fabs(a - b) < 1e-10;
            };

            if (p[0] < -1e-10)
            {
                if (fuzzy_equal(p.norm(), inner_radius))
                {
                    const double half_side = inner_radius / std::sqrt(2);
                    result[0] = -cylinder_length + d;

                    if (p[1] > 0)
                    {
                        result[1] = half_side;
                    }
                    else
                    {
                        result[1] = -half_side;
                    }

                    if (p[2] > 0)
                    {
                        result[2] = half_side;
                    }
                    else
                    {
                        result[2] = -half_side;
                    }
                }
                else
                {
                    const double half_side = outer_radius / std::sqrt(2);
                    result[0] = -cylinder_length;

                    if (p[1] > 0)
                    {
                        result[1] = half_side;
                    }
                    else
                    {
                        result[1] = -half_side;
                    }

                    if (p[2] > 0)
                    {
                        result[2] = half_side;
                    }
                    else
                    {
                        result[2] = -half_side;
                    }
                }
            }
            return result;
        };
    GridTools::transform(transform_function, shell_cylinder);

    //Final merge
    GridGenerator::merge_triangulations(fairing, shell_cylinder, tria);
    GridTools::rotate(-M_PI / 2, 1, tria);

    //Boundary ids
    for (auto cell : tria.active_cell_iterators())
    {
        for (size_t f = 0; f < GeometryInfo<3>::faces_per_cell; ++f)
        {
            if (cell->face(f)->at_boundary())
            {
                for (size_t v = 0; v < GeometryInfo<3>::vertices_per_face; ++v)
                {
                    const Point<3> current_point = cell->face(f)->vertex(v);
                    if (current_point[2] > 1e-10)
                    {
                        if (std::fabs(current_point.norm() - outer_radius) < 1e-10)
                        {
                            cell->face(f)->set_boundary_id(2);
                            break;
                        }
                    }

                    cell->face(f)->set_boundary_id(1);
                }
            }
        }
    }
}

void MeshCreators::apply_iges_boundary_desc(Triangulation<3, 3> &tria,
                                            const std::string &iges_file,
                                            const TaskReader::GeometryProperties &geometry)
{
    TopoDS_Shape shell_surface = OpenCASCADE::read_IGES(iges_file, 0.1);
    const double tolerance = OpenCASCADE::get_shape_tolerance(shell_surface);

    std::vector<TopoDS_Compound> compounds;
    std::vector<TopoDS_CompSolid> compsolids;
    std::vector<TopoDS_Solid> solids;
    std::vector<TopoDS_Shell> shells;
    std::vector<TopoDS_Wire> wires;

    OpenCASCADE::extract_compound_shapes(shell_surface,
                                         compounds,
                                         compsolids,
                                         solids,
                                         shells,
                                         wires);

    const double inner_radius = geometry.inner_radius;
    const double outer_radius = geometry.outer_radius;
    const double cylinder_length = geometry.cylinder_length;

    auto fuzzy_equal = [](double a, double b)
    {
        return std::abs(a - b) < 1e-10;
    };

    Assert(wires.size() > 0,
           ExcMessage("I could not find any wire in the CAD file you gave me. Bailing out."));

    tria.set_all_manifold_ids(1);

    static OpenCASCADE::NormalProjectionBoundary<3, 3> normal_projector(shell_surface, tolerance);
    tria.set_manifold(1, normal_projector);

    GridOut grid_out;
}
