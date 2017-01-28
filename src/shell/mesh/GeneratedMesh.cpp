#include "GeneratedMesh.hpp"
GeneratedMesh::GeneratedMesh(unsigned int n_global_refinements,
                             const MeshMarkersGroup &markers)
    :
    n_global_refinements(n_global_refinements),
    markers(markers)
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
    markers.apply_markers(tria);
}