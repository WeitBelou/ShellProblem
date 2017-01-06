#include <src/mesh/MeshUtilities.hpp>
#include "CircleMarker.hpp"
CircleMarker::CircleMarker(const dealii::types::boundary_id boundary_id,
                           const dealii::Point<3> &center,
                           const double radius,
                           const unsigned int axis)
    :
    boundary_id(boundary_id),
    center(center),
    radius(radius),
    axis(axis)
{

}

void CircleMarker::apply_boundary_ids(dealii::Triangulation<3, 3> &triangulation) const
{
    for (auto cell : triangulation.active_cell_iterators()) {
        for (unsigned int f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                dealii::Triangulation<3>::active_face_iterator face = cell->face(f);
                if (MeshUtilities::is_face_in_circle(face, center, radius, axis)) {
                    face->set_all_boundary_ids(boundary_id);
                }
            }
        }
    }
}
