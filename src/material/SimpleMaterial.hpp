#ifndef SHELL_PROBLEM_MATERIALS_HPP
#define SHELL_PROBLEM_MATERIALS_HPP

#include <deal.II/base/parameter_handler.h>
#include <deal.II/base/symmetric_tensor.h>
#include <deal.II/base/tensor.h>

namespace Material
{


class SimpleElasticity
{
public:
    SimpleElasticity(double E, double G);
    dealii::SymmetricTensor<4, 3> get_stress_strain_tensor() const;
private:
    const double E;
    const double G;
};

class SimpleHeat
{
public:
    SimpleHeat(const double thermal_diffusivity);
public:
    const double thermal_diffusivity;
};

}

#endif //SHELL_PROBLEM_MATERIALS_HPP
