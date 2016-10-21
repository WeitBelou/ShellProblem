#ifndef SHELL_PROBLEM_ELASTICITY_SOLVER_HPP
#define SHELL_PROBLEM_ELASTICITY_SOLVER_HPP

#include <boost/filesystem/path.hpp>

#include <deal.II/dofs/dof_handler.h>
#include <deal.II/fe/fe_q.h>
#include <deal.II/fe/fe_system.h>
#include <deal.II/base/quadrature_lib.h>

#include <deal.II/lac/constraint_matrix.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/sparsity_pattern.h>

#include "launcher/SimpleMaterial.hpp"
#include "mesh/MeshWrappers.hpp"

namespace Solvers
{

class ElasticitySolver
{
public:
    ElasticitySolver(const MeshWrappers::Mesh &mesh,
                 const Material::SimpleElasticity &elasticity);
    void run(const boost::filesystem::path &output_dir);
};

}


#endif //SHELL_PROBLEM_ELASTICITY_SOLVER_HPP
