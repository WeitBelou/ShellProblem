#pragma once

#include <deal.II/base/symmetric_tensor.h>
class Material
{
public:
    Material(const double E, const double G, const double thermal_diffusivity);
    dealii::SymmetricTensor<4, 3> get_stress_strain_tensor() const;
private:
    const double E;
    const double G;

    const double thermal_diffusivity;
};