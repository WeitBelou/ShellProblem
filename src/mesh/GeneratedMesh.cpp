#include "GeneratedMesh.hpp"
GeneratedMesh::GeneratedMesh(unsigned int n_global_refinements,
                             std::shared_ptr<MeshMarkerBase> marker)
    :
    n_global_refinements(n_global_refinements),
    marker(marker)
{}

void GeneratedMesh::create()
{
    create_coarse_mesh();
    apply_manifold_ids();
    refine_mesh(n_global_refinements);
    apply_boundary_ids();
}

void GeneratedMesh::refine_mesh(unsigned int n_refines)
{
    tria.refine_global(n_refines);
}

void GeneratedMesh::apply_boundary_ids()
{
    marker->mark_mesh(tria);
}