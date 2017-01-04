#ifndef SHELL_PROBLEM_HEAT_SOLVER_HPP
#define SHELL_PROBLEM_HEAT_SOLVER_HPP

#include <boost/filesystem/path.hpp>

#include <deal.II/grid/tria.h>
#include <deal.II/base/function.h>

#include <deal.II/lac/vector.h>
#include <deal.II/lac/sparse_matrix.h>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/fe/fe_q.h>
#include <deal.II/base/quadrature_lib.h>
#include <deal.II/lac/constraint_matrix.h>
#include <src/boundaries/BoundariesMap.hpp>
#include <src/linear_solver/LinearSolverBase.hpp>

#include "SolverBase.hpp"
#include "src/mesh/MeshBase.hpp"

class HeatSolver: public SolverBase
{
public:
    class Material
    {
    public:
        Material(const double thermal_diffusivity);
    public:
        const double thermal_diffusivity;
    };

    HeatSolver(std::shared_ptr<MeshBase> mesh,
               const Material &material,
               const BoundariesMap boundary_functions,
               const std::shared_ptr<LinearSolverBase> &linear_solver);
    ~HeatSolver();
protected:
    void setup_system() override;
    void assemble_system() override;
    unsigned int solve_linear_system() override;

    void do_postprocessing(const std::string &output_dir) override;

    unsigned int get_n_dofs() override;

private:
    Material material;

    const BoundariesMap boundary_functions;

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


#endif //SHELL_PROBLEM_HEAT_SOLVER_HPP
