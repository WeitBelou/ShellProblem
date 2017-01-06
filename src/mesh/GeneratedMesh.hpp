#ifndef SHELL_PROBLEM_GENERATED_MESH_HPP
#define SHELL_PROBLEM_GENERATED_MESH_HPP

#include <src/mesh_markers/MeshMarkersGroup.hpp>
#include "src/mesh_markers/MeshMarkerBase.hpp"
#include "MeshBase.hpp"
class GeneratedMesh: public MeshBase
{

public:
    GeneratedMesh(unsigned int n_global_refinements,
                  const MeshMarkersGroup &markers);
protected:
    virtual void create() final;

    virtual void create_coarse_mesh() = 0;
    virtual void apply_manifold_ids() = 0;
    virtual void apply_boundary_ids() final;

    void refine_mesh(unsigned int n_refines);

    unsigned int n_global_refinements;

    const MeshMarkersGroup markers;
};


#endif //SHELL_PROBLEM_GENERATED_MESH_HPP
