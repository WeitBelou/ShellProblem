#include <src/util/MeshUtilities.hpp>
#include "HalfSphereMarker.hpp"
HalfSphereMarker::HalfSphereMarker(const dealii::types::boundary_id &boundary_id,
                                   const dealii::Point<3> &center,
                                   const double radius,
                                   const dealii::Point<3> &orientation)
    : boundary_id(boundary_id), center(center), radius(radius), orientation(orientation)
{}

void HalfSphereMarker::apply_boundary_ids(dealii::Triangulation<3, 3> &mesh) const
{
    for (auto cell : mesh.active_cell_iterators()) {
        for (unsigned int f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                dealii::Triangulation<3>::active_face_iterator face = cell->face(f);
                if (MeshUtilities::is_face_on_half_sphere(face, center, radius, orientation)) {
                    face->set_all_boundary_ids(boundary_id);
                }
            }
        }
    }
}
