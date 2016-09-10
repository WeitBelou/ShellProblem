#include "MeshCreator.hpp"

#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/grid/grid_tools.h>

#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_out.h>

#include <fstream>

using namespace MeshCreators;
using namespace dealii;

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