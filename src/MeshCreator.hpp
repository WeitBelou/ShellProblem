#ifndef SHELL_PROBLEM_MESHCREATOR_HPP
#define SHELL_PROBLEM_MESHCREATOR_HPP

#include "deal.II/grid/tria.h"
#include "TaskReader.hpp"

namespace MeshCreators
{

void write_mesh(const dealii::Triangulation<3> &tria,
                const std::string &output_file);

void read_from_msh(dealii::Triangulation<3> &tria,
                   const std::string &input_file);
}

#endif //SHELL_PROBLEM_MESHCREATOR_HPP
