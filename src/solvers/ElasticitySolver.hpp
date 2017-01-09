#pragma once
#include <boost/filesystem/path.hpp>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/fe/fe_system.h>
#include <deal.II/base/quadrature_lib.h>
#include <deal.II/base/symmetric_tensor.h>

#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/sparsity_pattern.h>
#include <deal.II/lac/constraint_matrix.h>
#include <deal.II/lac/solver_gmres.h>

#include "linear_solver/LinearSolverBase.hpp"
#include "boundaries/BoundariesGroup.hpp"
#include "boundaries/Boundaries.hpp"

#include "SolverBase.hpp"

class ElasticitySolver: public SolverBase
{
public:
    class Material
    {
    public:
        Material(double E, double G);
        dealii::SymmetricTensor<4, 3> get_stress_strain_tensor() const;
    private:
        const double E;
        const double G;
    };

    ElasticitySolver(std::shared_ptr<MeshBase> mesh,
                     const Material &material,
                     const BoundariesGroup boundaries,
                     std::shared_ptr<LinearSolverBase> linear_solver);
    ~ElasticitySolver();
protected:
    void setup_system() override;
    void assemble_system() override;
    unsigned int solve_linear_system() override;
    void do_postprocessing(const std::string &output_dir) override;
    unsigned int get_n_dofs() override;
private:
    void compute_norm_of_stress();
    const BoundariesGroup boundaries;
    std::shared_ptr<LinearSolverBase> linear_solver;

    dealii::DoFHandler<3> dof_handler;

    dealii::Vector<double> norm_of_stress;
    const dealii::FESystem<3> fe;
    const dealii::FEValuesExtractors::Vector displacement_extractor;
    const dealii::QGauss<3> quadrature;

    const dealii::QGauss<2> face_quadrature;

    dealii::ConstraintMatrix constraints;
    const dealii::SymmetricTensor<4, 3> stress_strain;

    dealii::SparsityPattern sparsity_pattern;
    dealii::SparseMatrix<double> system_matrix;
    dealii::Vector<double> system_rhs;

    dealii::Vector<double> displacement;

    dealii::SolverGMRES<>::AdditionalData linear_solver_data;
};
