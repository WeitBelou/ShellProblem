#include <fstream>
#include "TaskUtil.hpp"

json TaskUtil::read_json_from_file(const std::string &task_file)
{
    json j;
    std::ifstream input(task_file);
    input >> j;
    return j;
}