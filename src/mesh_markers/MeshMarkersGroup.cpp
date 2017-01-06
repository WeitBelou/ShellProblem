#include "MeshMarkersGroup.hpp"

void MeshMarkersGroup::add_marker(std::shared_ptr<const MeshMarkerBase> marker)
{
    markers.push_back(marker);
}

void MeshMarkersGroup::apply_markers(dealii::Triangulation<3, 3> &tria) const
{
    for (auto&& marker : markers) {
        marker->mark_mesh(tria);
    }
}
