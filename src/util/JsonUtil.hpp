#ifndef SHELL_PROBLEM_JSON_UTIL_HPP
#define SHELL_PROBLEM_JSON_UTIL_HPP

#include <src/third_party/json.hpp>
#include <deal.II/base/point.h>

using json = nlohmann::json;

class JsonUtil
{
public:
    static json read_json_from_file(const std::string &task_file);
    static const dealii::Point<3, double> get_point(const json &point);
};

#endif //SHELL_PROBLEM_JSON_UTIL_HPP
