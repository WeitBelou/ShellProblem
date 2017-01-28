#pragma once
#include <deal.II/grid/tria.h>

class MeshMarkerBase
{
public:
    virtual void mark_mesh(dealii::Triangulation<3, 3> &mesh) const = 0;
};
