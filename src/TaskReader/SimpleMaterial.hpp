#ifndef SHELL_PROBLEM_MATERIALS_HPP
#define SHELL_PROBLEM_MATERIALS_HPP


#include <deal.II/base/parameter_handler.h>
#include <deal.II/base/tensor.h>

namespace Material
{

struct SimpleElasticity
{
    static void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);

    dealii::Tensor<4, 3> get_stress_strain_tensor() const;
private:
    double youngs_modulus;
    double shear_modulus;
};

struct SimpleHeat
{
    double thermal_diffusivity;

    static void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);
};

struct SimpleMaterial
{
    SimpleHeat heat;
    SimpleElasticity elasticity;

    static void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);
};

}

#endif //SHELL_PROBLEM_MATERIALS_HPP
