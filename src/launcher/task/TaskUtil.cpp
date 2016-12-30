#include <fstream>
#include "TaskUtil.hpp"

json get_json(const std::string &task_file)
{
    json j;
    std::ifstream input(task_file);
    input >> j;
    return j;
}