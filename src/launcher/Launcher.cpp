#include "Launcher.hpp"

#include "solvers/HeatSolver.hpp"

using namespace dealii;

using namespace TaskReader;

using namespace Material;
using namespace MeshWrappers;

void Launcher::run(const std::string &task_file, const std::string &output_dir)
{
    TaskFactory task_factory;
    auto task = task_factory.create_task(task_file, output_dir);
    task->execute();
}
