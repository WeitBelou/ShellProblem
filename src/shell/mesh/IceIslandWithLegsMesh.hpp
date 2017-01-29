#pragma once

#include "GeneratedMesh.hpp"
class IceIslandWithLegsMesh: public GeneratedMesh
{
public:

protected:
public:
    IceIslandWithLegsMesh(unsigned int n_global_refinements,
                              const MeshMarkersGroup &markers,
                              const double a,
                              const double h);
protected:
    void create_coarse_mesh() override;
    void apply_manifold_ids() override;

private:
    const double a;
    const double h;
};


