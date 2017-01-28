#pragma once
#include <deal.II/grid/tria.h>

class MeshBase
{
public:
    const dealii::Triangulation<3, 3> &mesh() const;
protected:
    dealii::Triangulation<3> tria;
};