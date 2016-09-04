#include "HeatSolver.hpp"

using namespace dealii;

HeatSolver::SimpleSolver::SimpleSolver(dealii::Triangulation<3> &mesh,
                                       const dealii::Function<3> &rhs_function,
                                       const dealii::Function<3> &fairing_conditions,
                                       const double a_square)
    :
    mesh(&mesh),
    dof_handler(mesh),
    rhs_function(&rhs_function),
    fairing_conditions(&fairing_conditions),
    fe(2),
    quadrature(2),
    a_square(a_square)
{

}

HeatSolver::SimpleSolver::~SimpleSolver()
{
    dof_handler.clear();
}

void HeatSolver::SimpleSolver::run(const boost::filesystem::path &output_dir)
{
    std::cout << "    Setup system..." << std::endl << std::flush;
    setup_system();
    std::cout << "    Number of degrees of freedom: " << dof_handler.n_dofs() << std::endl;

    std::cout << "    Assembling system..." << std::endl << std::flush;
    assemble_system();

    std::cout << "    Solving linear system..." << std::endl << std::flush;
    const size_t n_iter = solve_linear_system();
    std::cout << "    Solver conerges in " << n_iter << " iterations." << std::endl;

    std::cout << "    Output solution..." << std::endl << std::flush;
    output_solution(output_dir);
}

void HeatSolver::SimpleSolver::setup_system()
{
    dof_handler.distribute_dofs(fe);
}

void HeatSolver::SimpleSolver::assemble_system()
{

}

size_t HeatSolver::SimpleSolver::solve_linear_system()
{
    return 0;
}

void HeatSolver::SimpleSolver::output_solution(const boost::filesystem::path &output_dir)
{

}

void HeatSolver::SimpleSolver::assemble_system_matrix()
{

}

void HeatSolver::SimpleSolver::assemble_system_rhs()
{

}
