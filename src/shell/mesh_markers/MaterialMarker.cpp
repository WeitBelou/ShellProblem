#include "MaterialMarker.hpp"
void MaterialMarker::mark_mesh(dealii::Triangulation<3, 3> &mesh) const
{
    apply_material_ids(mesh);
}
