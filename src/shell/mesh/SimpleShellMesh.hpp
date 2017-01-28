#pragma once
#include "GeneratedMesh.hpp"

class SimpleShellMesh: public GeneratedMesh
{
public:
    SimpleShellMesh(double inner_radius,
                    double outer_radius,
                    double cylinder_length,
                    unsigned int n_refines,
                    const MeshMarkersGroup markers);
protected:
    virtual void create_coarse_mesh() override;
    virtual void apply_manifold_ids() override;
private:
    double inner_radius;
    double outer_radius;
    double thickness;
    double cylinder_length;
};
