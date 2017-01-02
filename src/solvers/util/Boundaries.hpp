#ifndef SHELL_PROBLEM_BOUNDARIES_HPP
#define SHELL_PROBLEM_BOUNDARIES_HPP

#include <memory>
#include <deal.II/base/point.h>
#include <deal.II/base/function.h>
#include <deal.II/dofs/function_map.h>


class DirichletBoundaries
{
public:
    DirichletBoundaries() = default;
    void add_function(dealii::types::boundary_id id, std::shared_ptr<const dealii::Function<3>> function);
    std::shared_ptr<const dealii::Function<3>> get_function_by_id(dealii::types::boundary_id id) const;

private:
    std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> boundary_functions;
};

class SinSquare: public dealii::Function<3>
{
public:
    SinSquare(double amplitude);

    virtual double value(const dealii::Point<3> &point, const unsigned int component = 0) const override;

    virtual dealii::Tensor<1, 3, double>
    gradient(const dealii::Point<3> &p, const unsigned int component = 0) const override;

    virtual void value_list(const std::vector<dealii::Point<3>> &points,
                            std::vector<double> &values,
                            const unsigned int component = 0) const override;

    virtual void gradient_list(const std::vector<dealii::Point<3>> &points,
                               std::vector<dealii::Tensor<1, 3, double>> &gradients,
                               const unsigned int component = 0) const override;
private:
    const double a;
};

#endif //SHELL_PROBLEM_BOUNDARIES_HPP
