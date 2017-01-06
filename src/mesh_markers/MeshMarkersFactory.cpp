#include "MeshMarkersFactory.hpp"
#include "CircleMarker.hpp"

const MeshMarkersGroup MeshMarkersFactory::create_mesh_markers(const json &mesh_markers_properties)
{
    MeshMarkersGroup markers;

    for (json marker: mesh_markers_properties) {
        if (marker["type"] == "circle_marker") {
            markers.add_marker(create_circle_marker(marker));
        }
        else {
            AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented())
        }
    }

    return markers;
}
std::shared_ptr<const MeshMarkerBase> MeshMarkersFactory::create_circle_marker(const json &marker)
{
    const dealii::types::boundary_id id = marker["id"].get<dealii::types::boundary_id>();
    const dealii::Point<3> center = JsonUtil::get_point(marker["center"]);
    const double radius = marker["radius"].get<double>();
    const unsigned axis = marker["axis"].get<unsigned>();
    return std::make_shared<CircleMarker>(id, center, radius, axis);
}
