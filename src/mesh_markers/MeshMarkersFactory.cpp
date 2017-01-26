#include "MeshMarkersFactory.hpp"
#include "CircleMarker.hpp"
#include "PlaneMarker.hpp"
#include "SphereMarker.hpp"
#include "HalfSphereMarker.hpp"
#include "TwoPlanesMarker.hpp"

const MeshMarkersGroup MeshMarkersFactory::create_mesh_markers(const json &mesh_markers_properties)
{
    MeshMarkersGroup markers;

    create_boundary_markers(mesh_markers_properties["boundary"], markers);
    create_material_markers(mesh_markers_properties["material"], markers);

    return markers;
}
void MeshMarkersFactory::create_boundary_markers(const json &mesh_markers_properties, MeshMarkersGroup &markers)
{
    for (json marker: mesh_markers_properties) {
        const std::string type = marker["type"].get<std::string>();

        if (type == "circle_marker") {
            markers.add_marker(create_circle_marker(marker));
        }
        else if (type == "plane_marker") {
            markers.add_marker(create_plane_marker(marker));
        }
        else if (type == "sphere_marker") {
            markers.add_marker(create_sphere_marker(marker));
        }
        else if (type == "half_sphere_marker") {
            markers.add_marker(create_half_sphere_marker(marker));
        }
        else {
            AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented(
                std::string("Boundary marker with type ") + type + " doesn\'t exist!"));
        }
    }
}

void MeshMarkersFactory::create_material_markers(const json &mesh_markers_properties, MeshMarkersGroup &markers)
{
    for (json marker: mesh_markers_properties) {
        const std::string type = marker["type"].get<std::string>();

        if (type == "two_planes") {
            markers.add_marker(create_two_planes_marker(marker));
        }
        else {
            AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented(
                std::string("Material marker with type ") + type + " doesn\'t exist!"));
        }
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
std::shared_ptr<const MeshMarkerBase> MeshMarkersFactory::create_half_sphere_marker(const json &marker)
{
    const dealii::types::boundary_id id = marker["id"].get<dealii::types::boundary_id>();
    const dealii::Point<3> center = JsonUtil::get_point(marker["center"]);
    const double radius = marker["radius"].get<double>();
    const dealii::Point<3> orientation = JsonUtil::get_point(marker["orientation"]);
    return std::make_shared<HalfSphereMarker>(id, center, radius, orientation);
}

std::shared_ptr<const MeshMarkerBase> MeshMarkersFactory::create_two_planes_marker(const json &marker)
{
    const dealii::types::boundary_id id = marker["id"].get<dealii::types::boundary_id>();
    const dealii::Point<3> point_on_first_plane = JsonUtil::get_point(marker["point_on_first_plane"]);
    const dealii::Point<3> point_on_second_plane = JsonUtil::get_point(marker["point_on_second_plane"]);
    unsigned axis = marker["axis"].get<unsigned>();

    return std::make_shared<const TwoPlanesMarker>(id, point_on_first_plane, point_on_second_plane, axis);
}
