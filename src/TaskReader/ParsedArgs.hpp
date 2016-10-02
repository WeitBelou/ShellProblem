#ifndef SHELL_PROBLEM_PARSED_ARGS_HPP
#define SHELL_PROBLEM_PARSED_ARGS_HPP

#include <boost/program_options.hpp>
#include "TaskReader.hpp"

namespace TaskReader
{

class ParsedArgs
{
public:
    ParsedArgs();

    void parse_args(int argc, char **argv);

    const std::string &get_output_dir() const;
    const std::string &get_task_file() const;
    GeometryType get_geometry_type() const;
    MaterialType get_material_type() const;
private:
    boost::program_options::options_description desc;

    std::string task_file;
    std::string output_dir;

    std::string geometry_type;
    std::string material_type;

    GeometryType get_geometry_type_from_string(const std::string &type) const;
    MaterialType get_material_type_from_string(const std::string &type) const;
};

}


#endif //SHELL_PROBLEM_PARSED_ARGS_HPP
