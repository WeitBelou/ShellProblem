#include <src/util/MeshUtilities.hpp>
#include "SphereMarker.hpp"


SphereMarker::SphereMarker(const dealii::types::boundary_id boundary_id,
                           const dealii::Point<3> center,
                           const double radius)
    :
    boundary_id(boundary_id),
    center(center),
    radius(radius)
{}

void SphereMarker::apply_boundary_ids(dealii::Triangulation<3, 3> &mesh) const
{
    for (auto cell : mesh.active_cell_iterators()) {
        for (unsigned int f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                dealii::Triangulation<3>::face_iterator face = cell->face(f);
                if (MeshUtilities::is_face_on_sphere(face, center, radius)) {
                    face->set_all_boundary_ids(boundary_id);
                }
            }
        }
    }
}
