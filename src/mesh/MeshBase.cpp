#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_tools.h>
#include "MeshBase.hpp"

MeshBase::MeshBase(unsigned int n_global_refinements)
    : n_global_refinements(n_global_refinements)
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