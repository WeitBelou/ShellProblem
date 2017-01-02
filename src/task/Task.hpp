#ifndef SHELL_PROBLEM_TASK_HPP
#define SHELL_PROBLEM_TASK_HPP

#include <src/solvers/SolverBase.hpp>

class Task
{
public:
    Task(std::shared_ptr<SolverBase> solver,
         const std::string output_dir);

    void execute();
private:
    const std::shared_ptr<SolverBase> solver;
    const std::string output_dir;
};


#endif //SHELL_PROBLEM_TASK_HPP
