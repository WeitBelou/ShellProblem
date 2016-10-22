#ifndef SHELL_PROBLEM_MATERIALS_HPP
#define SHELL_PROBLEM_MATERIALS_HPP

#include <deal.II/base/parameter_handler.h>
#include <deal.II/base/symmetric_tensor.h>
#include <deal.II/base/tensor.h>

namespace Material
{

struct SimpleElasticity
{
    static void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);

    dealii::SymmetricTensor<4, 3> get_stress_strain_tensor() const;
private:
    double E;
    double G;
};

struct SimpleHeat
{
    double thermal_diffusivity;

    static void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);
};

class SimpleMaterial
{
public:
    SimpleMaterial(const std::string &material_file);

    const SimpleHeat &get_heat() const;
    const SimpleElasticity &get_elasticity() const;
private:
    static void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);

    SimpleHeat heat;
    SimpleElasticity elasticity;
};

}

#endif //SHELL_PROBLEM_MATERIALS_HPP
