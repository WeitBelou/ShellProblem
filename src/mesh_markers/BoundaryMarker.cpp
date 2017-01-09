#include "BoundaryMarker.hpp"
void BoundaryMarker::mark_mesh(dealii::Triangulation<3, 3> &mesh) const
{
    apply_boundary_ids(mesh);
}
