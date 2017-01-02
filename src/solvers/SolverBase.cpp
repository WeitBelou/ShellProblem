#include <iostream>
#include <chrono>
#include <deal.II/base/logstream.h>
#include "SolverBase.hpp"

using namespace std::chrono;

SolverBase::SolverBase(const std::shared_ptr<Meshes::MeshBase> &mesh)
    :
    mesh(mesh)
{}

void SolverBase::run(const std::string &output_dir)
{
    do_logged_setup_system();
    do_logged_assemble_system();
    do_logged_solve_linear_system();
    do_logged_do_postprocessing(output_dir);
}
void SolverBase::do_logged_do_postprocessing(const std::string &output_dir)
{
    auto start = system_clock::now();
    dealii::deallog << "Do postprocessing..." << std::endl;
    dealii::deallog << "Results will be written in " << output_dir << std::endl;
    this->do_postprocessing(output_dir);
    auto end = system_clock::now();
    dealii::deallog << "It takes: " << duration_cast<duration<double>>(end - start).count() << "s" << std::endl;
}

void SolverBase::do_logged_solve_linear_system()
{
    auto start = system_clock::now();
    dealii::deallog << "Solving linear system..." << std::endl;
    const size_t n_iter = this->solve_linear_system();
    dealii::deallog << "Solver converges in " << n_iter << " iterations." << std::endl;
    auto end = system_clock::now();
    dealii::deallog << "It takes: " << duration_cast<duration<double>>(end - start).count() << "s" << std::endl;
}

void SolverBase::do_logged_assemble_system()
{
    auto start = system_clock::now();
    dealii::deallog << "Assembling system..." << std::endl;
    this->assemble_system();
    auto end = system_clock::now();
    dealii::deallog << "It takes: " << duration_cast<duration<double>>(end - start).count() << "s" << std::endl;
}

void SolverBase::do_logged_setup_system()
{
    auto start = system_clock::now();
    dealii::deallog << "Setup system..." << std::endl;
    this->setup_system();
    dealii::deallog << "Number of degrees of freedom: " << this->get_n_dofs() << std::endl;
    auto end = system_clock::now();
    dealii::deallog << "It takes: " << duration_cast<duration<double>>(end - start).count() << "s" << std::endl;
}
