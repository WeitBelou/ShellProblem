#include "Launcher.hpp"
#include <src/launcher/task/TaskFactory.hpp>

using namespace dealii;

void Launcher::run(const std::string &task_file, const std::string &output_dir)
{
    TaskFactory task_factory;
    auto task = task_factory.create_task(task_file, output_dir);
    task->execute();
}
