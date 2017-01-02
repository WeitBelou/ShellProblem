#ifndef SHELL_PROBLEM_SIMPLE_SHELL_MESH_HPP
#define SHELL_PROBLEM_SIMPLE_SHELL_MESH_HPP

#include "MeshBase.hpp"

class SimpleShellMesh: public MeshBase
{
public:
    SimpleShellMesh(double inner_radius,
                    double outer_radius,
                    double cylinder_length,
                    unsigned int n_refines);
protected:
    virtual void create_coarse_mesh() override;

    virtual void apply_manifold_ids() override;
    virtual void apply_boundary_ids() override;

private:
    double inner_radius;
    double outer_radius;
    double thickness;
    double cylinder_length;
};

#endif //SHELL_PROBLEM_SIMPLE_SHELL_MESH_HPP
