#include "Boundaries.hpp"

using namespace dealii;

void DirichletBoundaries::add_function(dealii::types::boundary_id id,
                                       std::shared_ptr<const dealii::Function<3>> function)
{

    boundary_functions.insert(std::make_pair<>(id, function));
}

std::shared_ptr<const dealii::Function<3>>
DirichletBoundaries::get_function_by_id(dealii::types::boundary_id id) const
{
    auto it = boundary_functions.find(id);

    Assert(it != boundary_functions.end(), ExcNotInitialized());

    return it->second;
}

SinSquare::SinSquare(double amplitude)
    : Function<3>(1), a(amplitude)
{

}

double SinSquare::value(const dealii::Point<3> &point, const unsigned int /*component*/) const
{
    const double z = point(2);

    return a * (z * z) / point.norm_square();
}

dealii::Tensor<1, 3> SinSquare::gradient(const dealii::Point<3> &p, const unsigned int /*component*/) const
{
    const double r = p.norm();
    const double x = p(0);
    const double y = p(1);
    const double z = p(2);

    Tensor<1, 3> grad;
    grad[0] = -4 * x * std::pow(z, 2.0) / std::pow(r, 3.0);
    grad[1] = -4 * y * std::pow(z, 2.0) / std::pow(r, 3.0);
    grad[2] = 2 * z / std::pow(r, 2.0) - 2 * std::pow(z, 3.0) / std::pow(r, 4.0);
    grad *= a;

    return grad;
}
void SinSquare::value_list(const std::vector<Point<3>> &points,
                           std::vector<double> &values,
                           const unsigned int /*component*/) const
{
    const size_t n_points = points.size();
    Assert(n_points == values.size(), ExcDimensionMismatch(n_points, values.size()));
    for (size_t j = 0; j < n_points; ++j) {
        values[j] = SinSquare::value(points[j]);
    }
}
void SinSquare::gradient_list(const std::vector<Point<3>> &points,
                              std::vector<Tensor<1, 3, double>> &gradients,
                              const unsigned int /*component*/) const
{
    const size_t n_points = points.size();
    Assert(n_points == gradients.size(),
           ExcDimensionMismatch(n_points, gradients.size()));
    for (size_t j = 0; j < n_points; ++j) {
        gradients[j] = SinSquare::gradient(points[j]);
    }
}
