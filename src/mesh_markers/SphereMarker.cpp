#include <src/mesh/MeshUtilities.hpp>
#include "SphereMarker.hpp"


SphereMarker::SphereMarker(const dealii::types::boundary_id boundary_id,
                           const dealii::Point<3> center,
                           const double outer_radius)
    :
    boundary_id(boundary_id),
    center(center),
    outer_radius(outer_radius)
{}

void SphereMarker::apply_boundary_ids(dealii::Triangulation<3, 3> &triangulation)
{
    for (auto cell : triangulation.active_cell_iterators()) {
        for (unsigned int f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                dealii::Triangulation<3>::face_iterator face = cell->face(f);
                if (MeshUtilities::is_face_on_sphere(face, center, outer_radius)) {
                    face->set_all_boundary_ids(boundary_id);
                }
            }
        }
    }
}
