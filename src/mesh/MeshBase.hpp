#ifndef SHELL_PROBLEM_MESH_BASE_HPP
#define SHELL_PROBLEM_MESH_BASE_HPP

#include <deal.II/grid/tria.h>
#include <src/mesh_markers/MeshMarkerBase.hpp>

class MeshBase
{
public:
    MeshBase(unsigned int n_global_refinements,
             std::shared_ptr<MeshMarkerBase> marker);
    const dealii::Triangulation<3, 3> &mesh() const;
protected:
    void create();

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() final;

    void refine_mesh(unsigned int n_refines);

    dealii::Triangulation<3> tria;
    unsigned int n_global_refinements;
    const std::shared_ptr<MeshMarkerBase> marker;
};

#endif //SHELL_PROBLEM_MESH_BASE_HPP
