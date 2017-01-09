#ifndef SHELL_PROBLEM_MESH_MARKER_BASE_HPP
#define SHELL_PROBLEM_MESH_MARKER_BASE_HPP

#include <deal.II/grid/tria.h>

class MeshMarkerBase
{
public:
    virtual void mark_mesh(dealii::Triangulation<3, 3> &mesh) const = 0;
};


#endif //SHELL_PROBLEM_MESH_MARKER_BASE_HPP
