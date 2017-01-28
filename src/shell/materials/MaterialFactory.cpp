#include <deal.II/base/logstream.h>
#include "MaterialFactory.hpp"

MaterialsGroup MaterialFactory::create_materials(const json &materials_properties)
{
    MaterialsGroup materials;
    for (const json &material: materials_properties) {
        const dealii::types::boundary_id id = material["id"].get<dealii::types::boundary_id>();
        const double E = material["E"].get<double>();
        const double G = material["G"].get<double>();
        const double thermal_diffusivity = material["thermal_diffusivity"].get<double>();

        materials.add_material(id, std::make_shared<const Material>(E, G, thermal_diffusivity));
    }
    return materials;
}
