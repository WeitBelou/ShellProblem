#ifndef SHELL_PROBLEM_TASK_FACTORY_HPP
#define SHELL_PROBLEM_TASK_FACTORY_HPP

#include <memory>
#include "Task.hpp"

enum class MaterialType
{
    Simple, InvalidType
};
enum class GeometryType
{
    Simple, Cube, InvalidType
};

class TaskFactory
{
public:
    std::unique_ptr<Task> create_task(const std::string &task_file);
private:

};


#endif //SHELL_PROBLEM_TASK_FACTORY_HPP
