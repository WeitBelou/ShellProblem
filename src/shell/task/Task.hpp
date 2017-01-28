#pragma once
#include "src/shell/solvers/SolverBase.hpp"

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
