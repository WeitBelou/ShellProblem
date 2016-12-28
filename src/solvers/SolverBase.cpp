#include <iostream>
#include "SolverBase.hpp"

void Solvers::SolverBase::run()
{
    std::cout << "    Setup system..." << std::endl << std::flush;
    setup_system();
    std::cout << "    Number of degrees of freedom: " << get_n_dofs() << std::endl;

    std::cout << "    Assembling system..." << std::endl << std::flush;
    assemble_system();

    std::cout << "    Solving linear system..." << std::endl << std::flush;
    const size_t n_iter = solve_linear_system();
    std::cout << "    Solver converges in " << n_iter << " iterations." << std::endl;

    std::cout << "    Do postprocessing..." << std::endl << std::flush;
    do_postprocessing();
}
