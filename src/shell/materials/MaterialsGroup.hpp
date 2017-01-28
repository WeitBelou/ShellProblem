#pragma once

#include <deal.II/grid/tria.h>
#include "Material.hpp"

class MaterialsGroup
{
public:
    MaterialsGroup() = default;

    void add_material(dealii::types::boundary_id id, std::shared_ptr<const Material> material);
    const std::shared_ptr<const Material> get_material_by_id(dealii::types::material_id id) const;
private:
    std::map<dealii::types::material_id, std::shared_ptr<const Material>> materials;
};


