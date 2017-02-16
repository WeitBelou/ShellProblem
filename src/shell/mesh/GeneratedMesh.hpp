#pragma once

#include "MeshBase.hpp"

class GeneratedMesh: public MeshBase
{

public:
    GeneratedMesh(unsigned int n_global_refinements);
protected:
    virtual void create() final;

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() = 0;
    virtual void apply_material_ids() = 0;

    void refine_mesh(unsigned int n_refines);

    unsigned int n_global_refinements;
};
