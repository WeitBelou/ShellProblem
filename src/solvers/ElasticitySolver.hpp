#ifndef SHELL_PROBLEM_ELASTICITY_SOLVER_HPP
#define SHELL_PROBLEM_ELASTICITY_SOLVER_HPP

#include <boost/filesystem/path.hpp>

namespace ElasticitySolver
{

class SimpleSolver
{
public:
    void run(const boost::filesystem::path &output_dir);
};

}


#endif //SHELL_PROBLEM_ELASTICITY_SOLVER_HPP
