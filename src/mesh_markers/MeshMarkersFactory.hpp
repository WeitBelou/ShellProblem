#pragma once
#include "util/JsonUtil.hpp"
#include "MeshMarkersGroup.hpp"

class MeshMarkersFactory
{
public:
    static const MeshMarkersGroup create_mesh_markers(const json &mesh_markers_properties);
private:
    static std::shared_ptr<const MeshMarkerBase> create_circle_marker(const json &marker);
    static std::shared_ptr<const MeshMarkerBase> create_plane_marker(const json &marker);
    static std::shared_ptr<const MeshMarkerBase> create_sphere_marker(const json &marker);
    static std::shared_ptr<const MeshMarkerBase> create_half_sphere_marker(const json &marker);
    static void create_boundary_markers(const json &mesh_markers_properties, MeshMarkersGroup &markers);
    static void create_material_markers(const json &mesh_markers_properties, MeshMarkersGroup &markers);
    static std::shared_ptr<const MeshMarkerBase> create_two_planes_marker(const json &marker);
};
