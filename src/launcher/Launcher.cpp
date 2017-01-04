#include "Launcher.hpp"
#include <deal.II/base/logstream.h>
#include <fstream>

#include "src/task/TaskFactory.hpp"

using namespace dealii;

void Launcher::run(const std::string &task_file, const std::string &output_dir)
{
    std::ofstream file_logstream;
    file_logstream.open(output_dir + "/log.txt");
    deallog.depth_console(1);
    deallog.attach(file_logstream);

    auto task = TaskFactory::create_task_from_json(TaskUtil::read_json_from_file(task_file), output_dir);
    task->execute();
}
