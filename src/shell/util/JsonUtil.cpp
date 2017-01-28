#include <fstream>
#include <deal.II/base/point.h>
#include "JsonUtil.hpp"

json JsonUtil::read_json_from_file(const std::string &task_file)
{
    json j;
    std::ifstream input(task_file);
    input >> j;
    return j;
}

const dealii::Point<3, double> JsonUtil::get_point(const json &point)
{
    return dealii::Point<3>(point["x"].get<double>(),
                            point["y"].get<double>(),
                            point["z"].get<double>());
}
