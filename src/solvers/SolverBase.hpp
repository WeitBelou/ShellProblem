#ifndef SHELLPROBLEM_SOLVERBASE_HPP
#define SHELLPROBLEM_SOLVERBASE_HPP

#include <boost/filesystem/path.hpp>
namespace Solvers
{

class SolverBase
{
public:
    void run();
protected:
    virtual void setup_system() = 0;
    virtual void assemble_system() = 0;
    virtual unsigned int solve_linear_system() = 0;
    virtual void do_postprocessing() = 0;

    virtual unsigned int get_n_dofs() = 0;
};

}


#endif //SHELLPROBLEM_SOLVERBASE_HPP
