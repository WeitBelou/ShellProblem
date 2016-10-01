#ifndef SHELL_PROBLEM_MESH_WRAPPERS_HPP
#define SHELL_PROBLEM_MESH_WRAPPERS_HPP

#include "deal.II/grid/tria.h"

#include "src/TaskReader/Geometry.hpp"


namespace MeshWrappers
{

class Mesh
{
public:
    const dealii::Triangulation<3, 3> &mesh() const;

    void write_msh(const std::string &output_file);
protected:
    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() = 0;

    void refine_mesh(size_t n_refines);

    dealii::Triangulation<3> tria;
};

class SimpleShellMesh : public Mesh
{
public:
    SimpleShellMesh(const Geometry::SimpleGeometry &geometry);

protected:
    virtual void create_coarse_mesh() override;
    virtual void apply_manifold_ids() override;
    virtual void apply_boundary_ids() override;

private:
    const double inner_radius;
    const double outer_radius;
    const double thickness;
    const double cylinder_length;

    const int n_refinements;
};

}

#endif //SHELL_PROBLEM_MESH_WRAPPERS_HPP
