#include "MaterialsGroup.hpp"
void MaterialsGroup::add_material(dealii::types::boundary_id id, std::shared_ptr<const Material> material)
{
    materials.insert(std::make_pair<>(id, material));
}

const std::shared_ptr<const Material> MaterialsGroup::get_material_by_id(dealii::types::material_id id) const
{
    return materials.find(id)->second;
}
