#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/grid_tools.h>
#include "MeshBase.hpp"

const dealii::Triangulation<3, 3> &MeshBase::mesh() const
{
    return tria;
}

