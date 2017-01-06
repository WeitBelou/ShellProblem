#ifndef SHELL_PROBLEM_MESH_MARKERS_FACTORY_HPP
#define SHELL_PROBLEM_MESH_MARKERS_FACTORY_HPP

#include "src/util/JsonUtil.hpp"
#include "MeshMarkersGroup.hpp"

class MeshMarkersFactory
{
public:
    static const MeshMarkersGroup create_mesh_markers(const json & mesh_markers_properties);
private:
    static std::shared_ptr<const MeshMarkerBase> create_circle_marker(const json &marker);
    static std::shared_ptr<const MeshMarkerBase> create_plane_marker(const json &marker);
    static std::shared_ptr<const MeshMarkerBase> create_sphere_marker(const json &marker);
};


#endif //SHELL_PROBLEM_MESH_MARKERS_FACTORY_HPP
