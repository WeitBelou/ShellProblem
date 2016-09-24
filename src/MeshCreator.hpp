#ifndef SHELL_PROBLEM_MESHCREATOR_HPP
#define SHELL_PROBLEM_MESHCREATOR_HPP

#include "deal.II/grid/tria.h"
#include "TaskReader.hpp"

namespace MeshCreators
{

void write_msh(const dealii::Triangulation<3> &tria,
               const std::string &output_file);

void read_from_msh(dealii::Triangulation<3> &tria,
                   const std::string &input_file);

void create_coarse_shell_mesh(dealii::Triangulation<3> &tria,
                              const TaskReader::GeometryProperties &geometry);

void apply_iges_boundary_desc(dealii::Triangulation<3, 3> &tria,
                              const std::string &iges_file,
                              const TaskReader::GeometryProperties &geometry);
}

#endif //SHELL_PROBLEM_MESHCREATOR_HPP
