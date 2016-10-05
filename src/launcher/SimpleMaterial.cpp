#include "SimpleMaterial.hpp"

using namespace dealii;

void Material::SimpleElasticity::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Elasticity");
    {
        prm.declare_entry("E", "7.0e11",
                          Patterns::Double(0),
                          "Young\'s modulus");
        prm.declare_entry("G", "2.6e11",
                          Patterns::Double(0),
                          "Shear modulus");
    }
    prm.leave_subsection();
}

void Material::SimpleElasticity::get_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Elasticity");
    {
        youngs_modulus = prm.get_double("E");
        shear_modulus = prm.get_double("G");
    }
    prm.leave_subsection();
}

Tensor<4, 3> Material::SimpleElasticity::get_stress_strain_tensor() const
{
    return Tensor<4, 3>();
}

void Material::SimpleHeat::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Heat");
    {
        prm.declare_entry("Thermal diffusivity", "4.4e-1",
                          Patterns::Double(0),
                          "Thermal diffusivity(a ^ 2)");
    }
    prm.leave_subsection();
}

void Material::SimpleHeat::get_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Heat");
    {
        thermal_diffusivity = prm.get_double("Thermal diffusivity");
    }
    prm.leave_subsection();
}

Material::SimpleMaterial::SimpleMaterial(const std::string &material_file)
{
    ParameterHandler prm;
    declare_parameters(prm);
    prm.parse_input(material_file);
    get_parameters(prm);
}

void Material::SimpleMaterial::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Material");
    {
        SimpleHeat::declare_parameters(prm);
        SimpleElasticity::declare_parameters(prm);
    }
    prm.leave_subsection();
}

void Material::SimpleMaterial::get_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Material");
    {
        heat.get_parameters(prm);
        elasticity.get_parameters(prm);
    }
    prm.leave_subsection();
}

const Material::SimpleHeat &Material::SimpleMaterial::get_heat() const
{
    return heat;
}

const Material::SimpleElasticity &Material::SimpleMaterial::get_elasticity() const
{
    return elasticity;
}
