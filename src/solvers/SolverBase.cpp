#include <iostream>
#include "SolverBase.hpp"

Solvers::SolverBase::SolverBase(const std::shared_ptr<Meshes::MeshBase> &mesh)
    :
    mesh(mesh)
{}

void Solvers::SolverBase::run(const std::string &output_dir)
{
    dealii::deallog << "    Setup system..." << std::endl << std::flush;
    setup_system();
    dealii::deallog << "    Number of degrees of freedom: " << get_n_dofs() << std::endl;

    dealii::deallog << "    Assembling system..." << std::endl << std::flush;
    assemble_system();

    dealii::deallog << "    Solving linear system..." << std::endl << std::flush;
    const size_t n_iter = solve_linear_system();
    dealii::deallog << "    Solver converges in " << n_iter << " iterations." << std::endl << std::flush;

    dealii::deallog << "    Do postprocessing..." << std::endl << std::flush;
    dealii::deallog << "    Results will be written in " <<  output_dir << std::endl << std::flush;
    do_postprocessing(output_dir);
}
