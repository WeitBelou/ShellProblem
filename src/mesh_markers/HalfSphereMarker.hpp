#pragma once
#include "BoundaryMarker.hpp"

class HalfSphereMarker: public BoundaryMarker
{
public:
    HalfSphereMarker(const dealii::types::boundary_id &boundary_id,
                     const dealii::Point<3> &center,
                     const double radius,
                     const dealii::Point<3> &orientation);
protected:
    void apply_boundary_ids(dealii::Triangulation<3, 3> &mesh) const override;
private:
    dealii::types::boundary_id boundary_id;
    const dealii::Point<3> center;
    const double radius;
    const dealii::Point<3> orientation;
};
