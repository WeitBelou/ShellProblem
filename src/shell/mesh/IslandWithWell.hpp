#pragma once
#include "GeneratedMesh.hpp"
class IslandWithWell: public GeneratedMesh
{
public:
    IslandWithWell(const dealii::Point<3> &well_position, double well_radius,
                   const dealii::Point<3> &force_position, double force_radius,
                   double island_radius, double height, unsigned n_global_refinements);
protected:
    void create_coarse_mesh() override final;
    void apply_manifold_ids() override final;
    void apply_boundary_ids() override final;
    void apply_material_ids() override final;
private:
    const dealii::Point<3> well_position;
    const double well_radius;
    const dealii::Point<3> force_position;
    const double force_radius;
    const double island_radius;
    const double height;
};