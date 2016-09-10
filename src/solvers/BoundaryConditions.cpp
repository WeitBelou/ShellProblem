#include <deal.II/numerics/vector_tools.h>
#include "BoundaryConditions.hpp"

using namespace BoundaryConditions;
using namespace dealii;

BoundaryFunctionsMap::BoundaryFunctionsMap(const FunctionPointerMap &functions_map)
    :
    functions_map(functions_map)
{

}
void BoundaryFunctionsMap::interpolate_boundary_values(const dealii::DoFHandler<3> &dof,
                                                       dealii::ConstraintMatrix &constraints,
                                                       const ComponentMask &component_mask)
{
    for (auto pair : functions_map)
    {
        VectorTools::interpolate_boundary_values(dof, pair.first,
                                                 *pair.second,
                                                 constraints,
                                                 component_mask);
    }
}
