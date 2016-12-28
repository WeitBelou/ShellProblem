#ifndef SHELL_PROBLEM_MESH_WRAPPERS_HPP
#define SHELL_PROBLEM_MESH_WRAPPERS_HPP

#include <deal.II/grid/tria.h>
#include <deal.II/base/parameter_handler.h>


namespace MeshWrappers
{

class Mesh
{
public:
    Mesh(unsigned int n_global_refinements);
    const dealii::Triangulation<3, 3> &mesh() const;
    void write_msh(const std::string &output_file);
protected:
    void create();

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() = 0;

    void refine_mesh(unsigned int n_refines);

    dealii::Triangulation<3> tria;
    unsigned int n_global_refinements;
};

class CubeMesh: public Mesh
{

protected:
public:
    CubeMesh(double size, unsigned int n_refines);
protected:
    virtual void create_coarse_mesh() override;
    virtual void apply_manifold_ids() override;
    virtual void apply_boundary_ids() override;
private:
    double size;
};

class SimpleShellMesh: public Mesh
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

}

#endif //SHELL_PROBLEM_MESH_WRAPPERS_HPP
