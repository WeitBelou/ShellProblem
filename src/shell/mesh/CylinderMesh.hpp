#pragma once
#include "GeneratedMesh.hpp"

class CylinderMesh: public GeneratedMesh
{
public:
    CylinderMesh(const double radius,
                 const double height,
                 const dealii::Point<3> &center,
                 unsigned int n_global_refinements);
protected:
    void create_coarse_mesh() override final;
    void apply_manifold_ids() override final;
    void apply_boundary_ids() override final;
    void apply_material_ids() override final;

private:
    const double radius;
    const double height;
    const dealii::Point<3> center;
};