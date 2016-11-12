#include "ParsedArgs.hpp"

namespace po = boost::program_options;
using namespace TaskReader;

ParsedArgs::ParsedArgs()
    :
    desc("Options")
{
    auto task_file_option = po::value<std::string>(&task_file);
    task_file_option->value_name("task")->required();

    auto output_dir_option = po::value<std::string>(&output_dir);
    output_dir_option->value_name("output")->default_value("./");

    desc.add_options()
            ("help,H", "Show help")
            ("task,T", task_file_option, "File with task")
            ("output,O", output_dir_option, "Output directory");
}

void ParsedArgs::parse_args(int argc, char **argv)
{
    po::variables_map vm;
    po::store(po::parse_command_line(argc, const_cast<const char * const *>(argv), desc), vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return;
    }

    po::notify(vm);
}

const std::string &ParsedArgs::get_output_dir() const
{
    return output_dir;
}

const std::string &ParsedArgs::get_task_file() const
{
    return task_file;
}