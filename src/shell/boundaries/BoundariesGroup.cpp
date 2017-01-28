#include <deal.II/numerics/vector_tools.h>
#include <deal.II/fe/fe_values.h>
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

void
BoundariesGroup::apply_dirichlet(const dealii::DoFHandler<3> &dof_handler, dealii::ConstraintMatrix &constraints) const
{
    for (const auto &it : dirichlet) {
        dealii::VectorTools::interpolate_boundary_values(dof_handler, it.first, *it.second,
                                                         constraints);
    }
}

const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> &
BoundariesGroup::get_neumann() const
{
    return neumann;
}
