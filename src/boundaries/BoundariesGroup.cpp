#include "Boundaries.hpp"
#include "BoundariesGroup.hpp"

void BoundariesGroup::add_dirichlet(dealii::types::boundary_id id, std::shared_ptr<const dealii::Function<3>> function)
{
    dirichlet.insert(std::make_pair<>(id, function));
}

void BoundariesGroup::add_neumann(dealii::types::boundary_id id,
                                std::shared_ptr<const dealii::Function<3>> function)
{
    neumann.insert(std::make_pair<>(id, function));
}

const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> &
BoundariesGroup::get_dirichlet() const
{
    return dirichlet;
}

const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> &
BoundariesGroup::get_neumann() const
{
    return neumann;
}
