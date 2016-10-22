#include "ElasticitySolver.hpp"

using namespace dealii;

Solvers::ElasticitySolver::ElasticitySolver(const MeshWrappers::Mesh &mesh,
                                             const Material::SimpleElasticity &elasticity)
    :
    dof_handler(mesh.mesh())
{

}

void Solvers::ElasticitySolver::run(const boost::filesystem::path &output_dir)
{
    std::cout << "    Setup system..." << std::endl << std::flush;
    setup_system();
    std::cout << "    Number of degrees of freedom: " << dof_handler.n_dofs() << std::endl;

    std::cout << "    Assembling system..." << std::endl << std::flush;
    assemble_system();

    std::cout << "    Solving linear system..." << std::endl << std::flush;
    const size_t n_iter = solve_linear_system();
    std::cout << "    Solver converges in " << n_iter << " iterations." << std::endl;

    std::cout << "    Output solution..." << std::endl << std::flush;
    output_solution(output_dir);
}

Solvers::ElasticitySolver::~ElasticitySolver()
{
    dof_handler.clear();
}

void Solvers::ElasticitySolver::setup_system()
{

}

void Solvers::ElasticitySolver::assemble_system()
{

}

size_t Solvers::ElasticitySolver::solve_linear_system()
{
    return 0;
}

void Solvers::ElasticitySolver::output_solution(const boost::filesystem::path &output_dir)
{

}
