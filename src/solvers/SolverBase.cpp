#include <iostream>
#include "SolverBase.hpp"

Solvers::SolverBase::SolverBase(const std::shared_ptr<Meshes::MeshBase> &mesh)
    :
    mesh(mesh)
{}

void Solvers::SolverBase::run(const std::string &output_dir)
{
    std::cout << "    Setup system..." << std::endl << std::flush;
    setup_system();
    std::cout << "    Number of degrees of freedom: " << get_n_dofs() << std::endl;

    std::cout << "    Assembling system..." << std::endl << std::flush;
    assemble_system();

    std::cout << "    Solving linear system..." << std::endl << std::flush;
    const size_t n_iter = solve_linear_system();
    std::cout << "    Solver converges in " << n_iter << " iterations." << std::endl << std::flush;

    std::cout << "    Do postprocessing..." << std::endl << std::flush;
    std::cout << "    Results will be written in " <<  output_dir << std::endl << std::flush;
    do_postprocessing(output_dir);
}
