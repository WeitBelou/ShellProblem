#ifndef SHELL_PROBLEM_PARSED_ARGS_HPP
#define SHELL_PROBLEM_PARSED_ARGS_HPP

#include <boost/program_options.hpp>

namespace TaskReader
{

class ParsedArgs
{
public:
    ParsedArgs();

    void parse_args(int argc, char **argv);

    const std::string &get_output_dir() const;
    const std::string &get_task_file() const;
private:
    boost::program_options::options_description desc;

    std::string task_file;
    std::string output_dir;
};

}


#endif //SHELL_PROBLEM_PARSED_ARGS_HPP
