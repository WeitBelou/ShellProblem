#ifndef SHELL_PROBLEM_MESHCREATOR_HPP
#define SHELL_PROBLEM_MESHCREATOR_HPP

#include "deal.II/grid/tria.h"

namespace MeshCreators
{

void create_shell_mesh(dealii::Triangulation<3> &tria,
                       const double r, const double d, const double L);

void write_mesh(const dealii::Triangulation<3> &tria,
                const std::string &output_file);

void read_from_msh(dealii::Triangulation<3> &tria,
                   const std::string &input_file);
}

#endif //SHELL_PROBLEM_MESHCREATOR_HPP
