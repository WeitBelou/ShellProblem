#pragma once
#include "BoundaryMarker.hpp"
class SphereMarker: public BoundaryMarker
{
protected:
public:
    SphereMarker(const dealii::types::boundary_id boundary_id,
                 const dealii::Point<3> center,
                 const double radius);
protected:
    void apply_boundary_ids(dealii::Triangulation<3, 3> &mesh) const override;
private:
    const dealii::types::boundary_id boundary_id;
    const dealii::Point<3> center;
    const double radius;
};
