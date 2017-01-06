#ifndef SHELL_PROBLEM_TASK_FACTORY_HPP
#define SHELL_PROBLEM_TASK_FACTORY_HPP

#include <memory>
#include "Task.hpp"
#include "src/util/JsonUtil.hpp"

class TaskFactory
{
public:
    static std::shared_ptr<Task> create_task_from_json(json task, const std::string &output_dir);

};


#endif //SHELL_PROBLEM_TASK_FACTORY_HPP
