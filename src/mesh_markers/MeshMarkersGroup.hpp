#ifndef SHELL_PROBLEM_MESH_MARKERS_GROUP_HPP
#define SHELL_PROBLEM_MESH_MARKERS_GROUP_HPP


#include <deal.II/base/types.h>
#include "MeshMarkerBase.hpp"

class MeshMarkersGroup
{
public:
    MeshMarkersGroup() = default;

    void add_marker(std::shared_ptr<const MeshMarkerBase> marker);
    void apply_markers(dealii::Triangulation<3> & tria) const;
private:
    std::vector<std::shared_ptr<const MeshMarkerBase>> markers;
};


#endif //SHELL_PROBLEM_MESH_MARKERS_GROUP_HPP
