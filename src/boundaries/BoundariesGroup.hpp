#ifndef SHELL_PROBLEM_BOUNDARIES_GROUP_HPP
#define SHELL_PROBLEM_BOUNDARIES_GROUP_HPP

#include <memory>
#include <deal.II/base/function.h>

class BoundariesGroup
{
public:
    BoundariesGroup() = default;

    void add_dirichlet(dealii::types::boundary_id id, std::shared_ptr<const dealii::Function<3>> function);
    void add_neumann(dealii::types::boundary_id id, std::shared_ptr<const dealii::Function<3>> function);

    const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> & get_dirichlet() const;
    const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> & get_neumann() const;
private:
    std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> dirichlet;
    std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> neumann;
};
#endif //SHELL_PROBLEM_BOUNDARIES_GROUP_HPP
