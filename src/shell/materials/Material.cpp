#include "Material.hpp"

Material::Material(const double E, const double G, const double thermal_diffusivity)
    :
    E(E),
    G(G),
    thermal_diffusivity(thermal_diffusivity)
{

}

dealii::SymmetricTensor<4, 3> Material::get_stress_strain_tensor() const
{
    const double lambda = G * (E - 2 * G) / (3 * G - E);
    const double mu = G;

    auto d = [](size_t i, size_t j)
    { return (i == j) ? (1) : (0); };

    dealii::SymmetricTensor<4, 3> tmp;

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            for (size_t k = 0; k < 3; ++k) {
                for (size_t m = 0; m < 3; ++m) {
                    tmp[i][j][k][m] = lambda * d(i, j) * d(k, m) + mu * (d(i, k) * d(j, m) + d(i, m) * d(j, k));
                }
            }
        }
    }

    return tmp;
}