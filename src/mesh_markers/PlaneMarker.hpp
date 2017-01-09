#pragma once
#include "BoundaryMarker.hpp"

class PlaneMarker: public BoundaryMarker
{
public:

protected:
public:
    PlaneMarker(const dealii::types::boundary_id boundary_id,
                    const dealii::Point<3> &point_on_plane,
                    const unsigned int axis);
protected:
    void apply_boundary_ids(dealii::Triangulation<3, 3> &mesh) const override;
private:
    const dealii::Point<3> point_on_plane;
    const unsigned int axis;
    const dealii::types::boundary_id boundary_id;
};
