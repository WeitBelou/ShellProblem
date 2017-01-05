#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_tools.h>
#include <src/mesh_markers/MeshMarkerBase.hpp>
#include "MeshBase.hpp"

MeshBase::MeshBase(unsigned int n_global_refinements, std::shared_ptr<MeshMarkerBase> marker)
    :
    n_global_refinements(n_global_refinements),
    marker(marker)
{}
void MeshBase::create()
{
    create_coarse_mesh();
    apply_manifold_ids();
    apply_boundary_ids();
    refine_mesh(n_global_refinements);
}

const dealii::Triangulation<3, 3> &MeshBase::mesh() const
{
    return tria;
}

void MeshBase::refine_mesh(unsigned int n_refines)
{
    tria.refine_global(n_refines);
}

void MeshBase::apply_boundary_ids()
{
    marker->mark_mesh(tria);
}
