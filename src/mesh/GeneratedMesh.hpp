#pragma once

#include "MeshBase.hpp"
#include "mesh_markers/MeshMarkersGroup.hpp"

class GeneratedMesh: public MeshBase
{

public:
    GeneratedMesh(unsigned int n_global_refinements,
                  const MeshMarkersGroup &markers);
protected:
    virtual void create() final;

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() final;

    void refine_mesh(unsigned int n_refines);

    unsigned int n_global_refinements;

    const MeshMarkersGroup markers;
};
