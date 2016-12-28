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

#include "src/solvers/util/Boundaries.hpp"
#include "SolverBase.hpp"
#include "src/mesh/MeshBase.hpp"

namespace Solvers
{

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

    HeatSolver(std::shared_ptr<Meshes::MeshBase> mesh,
               const Material &material,
               const boost::filesystem::path &output_dir);
    ~HeatSolver();
protected:
    void setup_system() override;
    void assemble_system() override;
    unsigned int solve_linear_system() override;
    void do_postprocessing() override;
    unsigned int get_n_dofs() override;

private:
    void output_solution(const boost::filesystem::path &output_dir);

    Material material;

    const boost::filesystem::path output_dir;

    dealii::DoFHandler<3> dof_handler;

    const SinSquare fairing_function;

    const dealii::FE_Q<3> fe;
    const dealii::QGauss<3> quadrature;
    const dealii::QGauss<3> face_quadrature;

    dealii::ConstraintMatrix constraints;

    dealii::SparsityPattern sparsity_pattern;
    dealii::SparseMatrix<double> system_matrix;
    dealii::Vector<double> system_rhs;
    dealii::Vector<double> solution;
};

}


#endif //SHELL_PROBLEM_HEAT_SOLVER_HPP
