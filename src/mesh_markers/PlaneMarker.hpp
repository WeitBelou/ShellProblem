#ifndef SHELL_PROBLEM_PLANE_MARKER_HPP
#define SHELL_PROBLEM_PLANE_MARKER_HPP

#include "MeshMarkerBase.hpp"

class PlaneMarker: public MeshMarkerBase
{
public:

protected:
public:
    PlaneMarker(const dealii::types::boundary_id boundary_id,
                    const dealii::Point<3> &point_on_plane,
                    const unsigned int axis);
protected:
    void apply_boundary_ids(dealii::Triangulation<3, 3> &triangulation) override;
private:
    const dealii::Point<3> point_on_plane;
    const unsigned int axis;
    const dealii::types::boundary_id boundary_id;
};


#endif //SHELL_PROBLEM_PLANE_MARKER_HPP
