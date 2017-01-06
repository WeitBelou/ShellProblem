#ifndef SHELLPROBLEM_GENERATEDMESH_HPP
#define SHELLPROBLEM_GENERATEDMESH_HPP

#include <src/mesh_markers/MeshMarkerBase.hpp>
#include "MeshBase.hpp"
class GeneratedMesh: public MeshBase
{

public:
    GeneratedMesh(unsigned int n_global_refinements,
                  std::shared_ptr<MeshMarkerBase> marker);
protected:
    virtual void create() final;

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() final;

    void refine_mesh(unsigned int n_refines);

    unsigned int n_global_refinements;

    const std::shared_ptr<MeshMarkerBase> marker;
};


#endif //SHELLPROBLEM_GENERATEDMESH_HPP
