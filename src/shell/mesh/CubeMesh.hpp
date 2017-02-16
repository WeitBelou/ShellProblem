#pragma once

#include "MeshBase.hpp"
#include "GeneratedMesh.hpp"

class CubeMesh: public GeneratedMesh
{
public:
    CubeMesh(const double size,
             const dealii::Point<3> &center,
             unsigned int n_refines);
protected:
    void create_coarse_mesh() override final;
    void apply_manifold_ids() override final;
    void apply_boundary_ids() override final;
    void apply_material_ids() override final;

private:
    const double size;
    const dealii::Point<3> center;
};
