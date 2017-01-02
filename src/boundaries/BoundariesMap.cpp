#include "Boundaries.hpp"
#include "BoundariesMap.hpp"

void BoundariesMap::add_function(dealii::types::boundary_id id,
                                       std::shared_ptr<const dealii::Function<3>> function)
{

    boundary_functions.insert(std::make_pair<>(id, function));
}
std::shared_ptr<const dealii::Function<3>>
BoundariesMap::get_function_by_id(dealii::types::boundary_id id) const
{
    auto it = boundary_functions.find(id);

    Assert(it != boundary_functions.end(), dealii::StandardExceptions::ExcNotInitialized());

    return it->second;
}
const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>>
BoundariesMap::conditions() const
{
    return boundary_functions;
}
