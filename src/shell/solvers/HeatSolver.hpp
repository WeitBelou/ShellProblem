#pragma once
#include <boost/filesystem/path.hpp>

#include <deal.II/grid/tria.h>
#include <deal.II/base/function.h>

#include <deal.II/lac/vector.h>
#include <deal.II/lac/sparse_matrix.h>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/fe/fe_q.h>
#include <deal.II/base/quadrature_lib.h>
#include <deal.II/lac/constraint_matrix.h>
#include <src/shell/materials/Material.hpp>
#include <src/shell/materials/MaterialsGroup.hpp>

#include "src/shell/boundaries/BoundariesGroup.hpp"
#include "src/shell/linear_solver/LinearSolverBase.hpp"
#include "SolverBase.hpp"

class HeatSolver: public SolverBase
{
public:
    HeatSolver(std::shared_ptr<MeshBase> mesh,
               const MaterialsGroup &materials,
               const BoundariesGroup boundaries,
               const std::shared_ptr<LinearSolverBase> &linear_solver);
    ~HeatSolver();
protected:
    void setup_system() override;
    void assemble_system() override;
    unsigned int solve_linear_system() override;

    void do_postprocessing(const std::string &output_dir) override;

    unsigned int get_n_dofs() override;

private:
    MaterialsGroup materials;

    const BoundariesGroup boundaries;

    std::shared_ptr<LinearSolverBase> linear_solver;

    dealii::DoFHandler<3> dof_handler;

    const dealii::FE_Q<3> fe;
    const dealii::QGauss<3> quadrature;
    const dealii::QGauss<3> face_quadrature;

    dealii::ConstraintMatrix constraints;

    dealii::SparsityPattern sparsity_pattern;
    dealii::SparseMatrix<double> system_matrix;
    dealii::Vector<double> system_rhs;
    dealii::Vector<double> solution;
};
