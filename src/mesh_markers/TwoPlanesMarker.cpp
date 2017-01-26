#include "util/MeshUtilities.hpp"
#include "TwoPlanesMarker.hpp"
TwoPlanesMarker::TwoPlanesMarker(const dealii::types::boundary_id id,
                                 const dealii::Point<3> point_on_first_plane,
                                 const dealii::Point<3> point_on_second_plane,
                                 const unsigned int axis)
    :
    id(id),
    point_on_first_plane(point_on_first_plane),
    point_on_second_plane(point_on_second_plane),
    axis(axis)
{

}

void TwoPlanesMarker::apply_material_ids(dealii::Triangulation<3, 3> &tria) const
{
    for (auto cell : tria.active_cell_iterators()) {
        if (MeshUtilities::is_cell_between_two_planes(cell,
                                                      point_on_first_plane,
                                                      point_on_second_plane,
                                                      axis)) {
            cell->set_material_id(id);
        }
    }
}
