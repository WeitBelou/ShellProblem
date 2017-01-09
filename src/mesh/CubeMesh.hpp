#ifndef SHELL_PROBLEM_CUBE_MESH_HPP
#define SHELL_PROBLEM_CUBE_MESH_HPP

#include <src/mesh_markers/MeshMarkerBase.hpp>
#include "MeshBase.hpp"
#include "GeneratedMesh.hpp"

class CubeMesh: public GeneratedMesh
{
public:
    CubeMesh(const double size,
             const dealii::Point<3> & center,
             unsigned int n_refines,
             const MeshMarkersGroup marker);
protected:
    virtual void create_coarse_mesh() override;
    virtual void apply_manifold_ids() override;
private:
    const double size;
    const dealii::Point<3> center;
};

#endif //SHELL_PROBLEM_CUBE_MESH_HPP
