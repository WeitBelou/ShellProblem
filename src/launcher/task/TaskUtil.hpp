#ifndef SHELL_PROBLEM_TASK_UTIL_HPP
#define SHELL_PROBLEM_TASK_UTIL_HPP

#include <src/third_party/json.hpp>

using json = nlohmann::json;

json get_json(const std::string &task_file);

#endif //SHELL_PROBLEM_TASK_UTIL_HPP
