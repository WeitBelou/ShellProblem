#include "SimpleMaterial.hpp"

using namespace dealii;

Material::SimpleHeat::SimpleHeat(const double thermal_diffusivity)
    : thermal_diffusivity(thermal_diffusivity)
{}

Material::SimpleElasticity::SimpleElasticity(double E, double G)
    : E(E), G(G)
{}
SymmetricTensor<4, 3> Material::SimpleElasticity::get_stress_strain_tensor() const
{
    const double lambda = G * (E - 2 * G) / (3 * G - E);
    const double mu = G;

    auto d = [](size_t i, size_t j)
    { return (i == j) ? (1) : (0); };

    SymmetricTensor<4, 3> tmp;

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
