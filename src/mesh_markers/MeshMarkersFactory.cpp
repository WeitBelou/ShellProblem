#include "MeshMarkersFactory.hpp"
#include "CircleMarker.hpp"
#include "PlaneMarker.hpp"
#include "SphereMarker.hpp"

const MeshMarkersGroup MeshMarkersFactory::create_mesh_markers(const json &mesh_markers_properties)
{
    MeshMarkersGroup markers;

    for (json marker: mesh_markers_properties) {
        MeshMarkerType type = get_type(marker["type"]);
        switch (type) {
            case MeshMarkerType::CircleMarkerType:
                markers.add_marker(create_circle_marker(marker));
                break;
            case MeshMarkerType::PlaneMarkerType:
                markers.add_marker(create_plane_marker(marker));
                break;
            case MeshMarkerType::SphereMarkerType:
                markers.add_marker(create_sphere_marker(marker));
                break;
        }
    }

    return markers;
}

MeshMarkersFactory::MeshMarkerType MeshMarkersFactory::get_type(const json &type)
{
    const std::string type_string = type.get<std::string>();
    if (type == "circle_marker") {
        return MeshMarkerType::CircleMarkerType;
    }
    if (type == "plane_marker") {
        return MeshMarkerType::PlaneMarkerType;
    }
    if (type == "sphere_marker") {
        return MeshMarkerType::SphereMarkerType;
    }
    else {
        AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented(
            std::string("Mesh marker with name ") + type_string + " doesn\'t exist!"));
    }
}

std::shared_ptr<const MeshMarkerBase> MeshMarkersFactory::create_circle_marker(const json &marker)
{
    const dealii::types::boundary_id id = marker["id"].get<dealii::types::boundary_id>();
    const dealii::Point<3> center = JsonUtil::get_point(marker["center"]);
    const double radius = marker["radius"].get<double>();
    const unsigned axis = marker["axis"].get<unsigned>();
    return std::make_shared<CircleMarker>(id, center, radius, axis);
}

std::shared_ptr<const MeshMarkerBase> MeshMarkersFactory::create_plane_marker(const json &marker)
{
    const dealii::types::boundary_id id = marker["id"].get<dealii::types::boundary_id>();
    const dealii::Point<3> point_on_plane = JsonUtil::get_point(marker["point_on_plane"]);
    const unsigned axis = marker["axis"].get<unsigned>();
    return std::make_shared<PlaneMarker>(id, point_on_plane, axis);
}

std::shared_ptr<const MeshMarkerBase> MeshMarkersFactory::create_sphere_marker(const json &marker)
{
    const dealii::types::boundary_id id = marker["id"].get<dealii::types::boundary_id>();
    const dealii::Point<3> center = JsonUtil::get_point(marker["center"]);
    const double radius = marker["radius"].get<double>();
    return std::make_shared<SphereMarker>(id, center, radius);
}
