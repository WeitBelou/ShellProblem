#ifndef SHELL_PROBLEM_MESH_BASE_HPP
#define SHELL_PROBLEM_MESH_BASE_HPP

#include <deal.II/grid/tria.h>

class MeshBase
{
public:
    const dealii::Triangulation<3, 3> &mesh() const;
protected:
    dealii::Triangulation<3> tria;
};

#endif //SHELL_PROBLEM_MESH_BASE_HPP
