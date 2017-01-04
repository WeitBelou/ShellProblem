#ifndef SHELL_PROBLEM_MESH_MARKER_BASE_HPP
#define SHELL_PROBLEM_MESH_MARKER_BASE_HPP

#include <deal.II/grid/tria.h>

class MeshMarkerBase
{
public:
    void mark_mesh(dealii::Triangulation<3, 3> &mesh);
protected:
    virtual void apply_boundary_ids(dealii::Triangulation<3, 3> &triangulation) = 0;
};


#endif //SHELL_PROBLEM_MESH_MARKER_BASE_HPP
