#include "MaterialsGroup.hpp"
void MaterialsGroup::add_material(dealii::types::boundary_id id, std::shared_ptr<const Material> material)
{
    materials.insert(std::make_pair<>(id, material));
}

const std::shared_ptr<const Material> MaterialsGroup::get_material_by_id(dealii::types::material_id id) const
{
    AssertThrow(materials.count(id) != 0,
                dealii::ExcInternalError(std::string("Element with id: ") + std::to_string(id) + " not in materials"));
    return materials.find(id)->second;
}
