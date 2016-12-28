#ifndef SHELL_PROBLEM_CUBE_MESH_HPP
#define SHELL_PROBLEM_CUBE_MESH_HPP

#include "MeshBase.hpp"


namespace Meshes
{

class CubeMesh: public MeshBase
{

protected:
public:
    CubeMesh(double size, unsigned int n_refines);
protected:
    virtual void create_coarse_mesh() override;
    virtual void apply_manifold_ids() override;
    virtual void apply_boundary_ids() override;
private:
    double size;
};

}

#endif //SHELL_PROBLEM_CUBE_MESH_HPP
