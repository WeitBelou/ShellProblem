#include "Launcher.hpp"
#include <src/launcher/task/TaskFactory.hpp>
#include <src/launcher/task/TaskUtil.hpp>

using namespace dealii;

void Launcher::run(const std::string &task_file, const std::string &output_dir)
{
    TaskFactory task_factory(output_dir);
    auto task = task_factory.create_task_from_json(get_json(task_file));
    task->execute();
}
