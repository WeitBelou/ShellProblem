#pragma once

#include "MaterialMarker.hpp"
class TwoPlanesMarker : public MaterialMarker
{
public:
protected:
public:
    TwoPlanesMarker(const dealii::types::boundary_id id,
                        const dealii::Point<3> point_on_first_plane,
                        const dealii::Point<3> point_on_second_plane,
                        const unsigned int axis);
protected:
    void apply_material_ids(dealii::Triangulation<3, 3> &tria) const override;
private:
    const dealii::types::boundary_id id;
    const dealii::Point<3> point_on_first_plane;
    const dealii::Point<3> point_on_second_plane;
    const unsigned axis;
};


