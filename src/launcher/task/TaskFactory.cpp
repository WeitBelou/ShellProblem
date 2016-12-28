#include "TaskFactory.hpp"

std::unique_ptr<Task> TaskFactory::create_task(const std::string &task_file)
{
    return std::unique_ptr<Task>();
}
