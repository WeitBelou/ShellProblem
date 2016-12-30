#ifndef SHELL_PROBLEM_SOLVER_BASE_HPP
#define SHELL_PROBLEM_SOLVER_BASE_HPP

#include <deal.II/grid/tria.h>
#include <boost/filesystem/path.hpp>
#include "src/mesh/MeshBase.hpp"
#include "src/solvers/postprocessors/Postprocessor.hpp"
namespace Solvers
{

class SolverBase
{
public:
    SolverBase(const std::shared_ptr<Meshes::MeshBase> &mesh);

    void run(const std::string &output_dir);
protected:
    virtual void setup_system() = 0;
    virtual void assemble_system() = 0;
    virtual unsigned int solve_linear_system() = 0;
    virtual void do_postprocessing(const std::string &output_dir) = 0;

    virtual unsigned int get_n_dofs() = 0;

    const std::shared_ptr<Meshes::MeshBase> mesh;
};

}


#endif //SHELL_PROBLEM_SOLVER_BASE_HPP
