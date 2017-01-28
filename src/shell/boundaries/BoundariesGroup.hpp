#pragma once
#include <memory>

#include <deal.II/base/function.h>
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/fe/fe_system.h>
#include <deal.II/base/quadrature_lib.h>
#include <deal.II/base/symmetric_tensor.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/constraint_matrix.h>
#include <deal.II/lac/solver_gmres.h>
#include "src/shell/linear_solver/LinearSolverBase.hpp"
#include "BoundariesGroup.hpp"

class BoundariesGroup
{
public:
    BoundariesGroup() = default;

    void add_dirichlet(dealii::types::boundary_id id, std::shared_ptr<const dealii::Function<3>> function);
    void add_neumann(dealii::types::boundary_id id, std::shared_ptr<const dealii::Function<3>> function);

    void apply_dirichlet(const dealii::DoFHandler<3> &dof_handler, dealii::ConstraintMatrix &constraints) const;
    const std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> &get_neumann() const;
private:
    std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> dirichlet;
    std::map<dealii::types::boundary_id, std::shared_ptr<const dealii::Function<3>>> neumann;
};
