#pragma once
#include <memory>

#include "Task.hpp"
#include "util/JsonUtil.hpp"

class TaskFactory
{
public:
    static std::shared_ptr<Task> create_task_from_json(json task, const std::string &output_dir);

};
