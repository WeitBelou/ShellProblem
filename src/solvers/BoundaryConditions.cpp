#include "BoundaryConditions.hpp"

using namespace BoundaryConditions;
using namespace dealii;

SinSquareFunction::SinSquareFunction(const double A)
    :
    Function<3>(1),
    A(A)
{

}

double SinSquareFunction::value(const Point<3> &p, const size_t /*component*/) const
{
    const double sin_square = 1 - (p[2] * p[2]) / p.norm_square();

    return A * sin_square;
}
