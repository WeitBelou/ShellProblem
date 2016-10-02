#ifndef SHELL_PROBLEM_MESH_WRAPPERS_HPP
#define SHELL_PROBLEM_MESH_WRAPPERS_HPP

#include <deal.II/grid/tria.h>
#include <deal.II/base/parameter_handler.h>


namespace MeshWrappers
{

class Mesh
{
public:
    const dealii::Triangulation<3, 3> &mesh() const;

    void write_msh(const std::string &output_file);
protected:
    virtual void get_parameters(dealii::ParameterHandler &prm) = 0;

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() = 0;

    void refine_mesh(size_t n_refines);

    dealii::Triangulation<3> tria;
};

class CubeMesh: public Mesh
{
public:
    CubeMesh(dealii::ParameterHandler &prm);

    static void declare_parameters(dealii::ParameterHandler &prm);
protected:
    virtual void get_parameters(dealii::ParameterHandler &prm) override;

    virtual void create_coarse_mesh() override;
    virtual void apply_manifold_ids() override;
    virtual void apply_boundary_ids() override;
private:
    double size;

    int n_global_refinements;
};

class SimpleShellMesh: public Mesh
{
public:
    SimpleShellMesh(dealii::ParameterHandler &prm);

    static void declare_parameters(dealii::ParameterHandler &prm);
protected:
    virtual void get_parameters(dealii::ParameterHandler &prm) override;

    virtual void create_coarse_mesh() override;
    virtual void apply_manifold_ids() override;
    virtual void apply_boundary_ids() override;

private:
    double inner_radius;
    double outer_radius;
    double thickness;
    double cylinder_length;

    int n_global_refinements;
};

}

#endif //SHELL_PROBLEM_MESH_WRAPPERS_HPP
