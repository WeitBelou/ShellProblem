#ifndef SHELL_PROBLEM_BOUNDARY_CONDITIONS_HPP
#define SHELL_PROBLEM_BOUNDARY_CONDITIONS_HPP

#include <deal.II/base/function.h>

namespace BoundaryConditions
{

class SinSquareFunction: public dealii::Function<3>
{
public:
    SinSquareFunction(const double A);

    virtual double value(const dealii::Point<3> &p,
                         const size_t component = 0) const override;
private:
    const double A;
};

}


#endif //SHELL_PROBLEM_BOUNDARY_CONDITIONS_HPP
