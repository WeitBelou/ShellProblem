#include <src/mesh/MeshUtilities.hpp>
#include "PlaneMarker.hpp"
PlaneMarker::PlaneMarker(const dealii::types::boundary_id boundary_id,
                         const dealii::Point<3> &point_on_plane,
                         const unsigned int axis)
    : point_on_plane(point_on_plane), axis(axis), boundary_id(boundary_id)
{}

void PlaneMarker::apply_boundary_ids(dealii::Triangulation<3, 3> &triangulation) const
{
    for (auto cell : triangulation.active_cell_iterators()) {
        for (unsigned int f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                dealii::Triangulation<3>::active_face_iterator face = cell->face(f);
                if (MeshUtilities::is_face_on_plane(face, point_on_plane, axis)) {
                    face->set_all_boundary_ids(boundary_id);
                }
            }
        }
    }
}
