#include "Task.hpp"

Task::Task(std::shared_ptr<Solvers::SolverBase> solver, const std::string output_dir)
    :
    solver(solver), output_dir(output_dir)
{

}

void Task::execute()
{
    solver->run(output_dir);
}
