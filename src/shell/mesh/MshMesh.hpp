#pragma once
#include "MeshBase.hpp"
#include "src/shell/mesh_markers/MeshMarkersGroup.hpp"
class MshMesh : public MeshBase
{
public:
    MshMesh(const std::string &grid_file_name,
            const MeshMarkersGroup &markers);

private:

};


