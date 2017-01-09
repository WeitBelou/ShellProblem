#pragma once
#include <deal.II/base/point.h>
#include "third_party/json.hpp"

using json = nlohmann::json;

class JsonUtil
{
public:
    static json read_json_from_file(const std::string &task_file);
    static const dealii::Point<3, double> get_point(const json &point);
};
