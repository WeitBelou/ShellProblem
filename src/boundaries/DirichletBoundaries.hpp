#ifndef SHELLPROBLEM_DIRICHLETBOUNDARIES_HPP
#define SHELLPROBLEM_DIRICHLETBOUNDARIES_HPP

#include <memory>
#include <deal.II/base/function.h>

class DirichletBoundaries
{
public:
    DirichletBoundaries() = default;

    void add_function(dealii::types::boundary_id id, std::shared_ptr<const dealii::Function<3>> function);
    std::shared_ptr<const dealii::Function<3>> get_function_by_id(dealii::types::boundary_id id) const;
    const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> conditions() const;
private:
    std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> boundary_functions;
};
#endif //SHELLPROBLEM_DIRICHLETBOUNDARIES_HPP
