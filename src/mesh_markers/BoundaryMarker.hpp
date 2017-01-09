#ifndef SHELL_PROBLEM_BOUNDARY_MARKER_HPP
#define SHELL_PROBLEM_BOUNDARY_MARKER_HPP

#include "MeshMarkerBase.hpp"

class BoundaryMarker: public MeshMarkerBase
{
public:
    void mark_mesh(dealii::Triangulation<3, 3> &mesh) const override;
protected:
    virtual void apply_boundary_ids(dealii::Triangulation<3, 3> &mesh) const = 0;
};


#endif //SHELL_PROBLEM_BOUNDARY_MARKER_HPP
