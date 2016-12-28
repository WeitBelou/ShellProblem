#include "Task.hpp"

Task::Task(std::shared_ptr<Solvers::SolverBase> solver)
    :
    solver(solver)
{

}

void Task::execute()
{
    solver->run();
}
