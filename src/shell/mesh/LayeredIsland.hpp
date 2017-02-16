#pragma once
#include "GeneratedMesh.hpp"
class LayeredIsland: public GeneratedMesh
{
public:
    LayeredIsland(const double layer_height,
                  const dealii::Point<3> &force_position,
                  const double island_radius,
                  const double force_radius,
                  const double height,
                  unsigned int n_global_refinements);
protected:
    void create_coarse_mesh() override final;
    void apply_manifold_ids() override final;
    void apply_boundary_ids() override final;
    void apply_material_ids() override final;
private:
    const double layer_height;
    const double n_layers = 2;

    const dealii::Point<3> force_position;

    const double island_radius;
    const double force_radius;
    const double height;
};