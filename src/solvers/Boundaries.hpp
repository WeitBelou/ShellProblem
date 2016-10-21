#ifndef SHELLPROBLEM_BOUNDARIES_HPP
#define SHELLPROBLEM_BOUNDARIES_HPP

#include <deal.II/base/point.h>
#include <deal.II/base/function.h>

namespace Solvers
{

class SinSquare: public dealii::Function<3>
{
public:
    SinSquare(double amplitude);

    double value(const dealii::Point<3> &point, size_t component = 0) const override;

    virtual dealii::Tensor<1, 3>
    gradient(const dealii::Point<3> &p, const size_t component = 0) const override;
private:
    const double a;
};

}

#endif //SHELLPROBLEM_BOUNDARIES_HPP
