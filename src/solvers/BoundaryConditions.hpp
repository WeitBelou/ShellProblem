#ifndef SHELL_PROBLEM_BOUNDARY_CONDITIONS_HPP
#define SHELL_PROBLEM_BOUNDARY_CONDITIONS_HPP

#include <deal.II/base/function.h>
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/lac/constraint_matrix.h>
#include <deal.II/fe/component_mask.h>

namespace BoundaryConditions
{

class BoundaryFunctionsMap
{
public:
    typedef std::map<dealii::types::boundary_id,
                                        const dealii::SmartPointer<const dealii::Function<3>>> FunctionPointerMap;

    BoundaryFunctionsMap(const FunctionPointerMap &functions_map);

    void interpolate_boundary_values(const dealii::DoFHandler<3> &dof,
                                     dealii::ConstraintMatrix &constraints,
                                     const dealii::ComponentMask &component_mask = dealii::ComponentMask());
private:
    FunctionPointerMap functions_map;
};

}


#endif //SHELL_PROBLEM_BOUNDARY_CONDITIONS_HPP
