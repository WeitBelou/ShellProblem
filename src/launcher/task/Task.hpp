#ifndef SHELL_PROBLEM_TASK_HPP
#define SHELL_PROBLEM_TASK_HPP

#include <src/solvers/SolverBase.hpp>

class Task
{
public:
    Task(std::shared_ptr<Solvers::SolverBase> solver);

    void execute();
private:
    const std::shared_ptr<Solvers::SolverBase> solver;
};


#endif //SHELL_PROBLEM_TASK_HPP
