#include "Launcher.hpp"
#include <deal.II/base/logstream.h>
#include <fstream>

#include "src/launcher/task/TaskFactory.hpp"
#include "src/launcher/task/TaskUtil.hpp"

using namespace dealii;

Launcher::Launcher()
{
}

void Launcher::run(const std::string &task_file, const std::string &output_dir)
{
    std::ofstream file_logstream;
    file_logstream.open(output_dir + "/log.txt");
    deallog.depth_console(1);
    deallog.attach(file_logstream);

    TaskFactory task_factory(output_dir);
    auto task = task_factory.create_task_from_json(TaskUtil::read_json_from_file(task_file));
    task->execute();
}
