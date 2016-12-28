#ifndef SHELL_PROBLEM_MESH_BASE_HPP
#define SHELL_PROBLEM_MESH_BASE_HPP

#include <deal.II/grid/tria.h>


namespace Meshes
{
class MeshBase
{
public:
    MeshBase(unsigned int n_global_refinements);
    const dealii::Triangulation<3, 3> &mesh() const;
protected:
    void create();

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() = 0;

    void refine_mesh(unsigned int n_refines);

    dealii::Triangulation<3> tria;
    unsigned int n_global_refinements;
};

}
#endif //SHELL_PROBLEM_MESH_BASE_HPP
