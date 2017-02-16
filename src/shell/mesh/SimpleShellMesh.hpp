#pragma once
#include "GeneratedMesh.hpp"

class SimpleShellMesh: public GeneratedMesh
{
public:
    SimpleShellMesh(double inner_radius,
                    double outer_radius,
                    double cylinder_length,
                    unsigned int n_refines);
protected:
    void create_coarse_mesh() override final;
    void apply_manifold_ids() override final;
    void apply_boundary_ids() override final;
    void apply_material_ids() override final;

private:
    double inner_radius;
    double outer_radius;
    double thickness;
    double cylinder_length;
};
