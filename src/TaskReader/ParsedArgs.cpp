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

    auto geometry_type_option = po::value<std::string>(&geometry_type);
    geometry_type_option->value_name("geometry")->default_value("");

    auto material_type_option = po::value<std::string>(&material_type);
    material_type_option->value_name("material")->default_value("");

    desc.add_options()
            ("help,H", "Show help")
            ("task,T", task_file_option, "File with task")
            ("output,O", output_dir_option, "Output directory")
            ("material,M", material_type_option, "Material type")
            ("geometry,G", geometry_type_option, "Geometry type");
}

void ParsedArgs::parse_args(int argc, char **argv)
{
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

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

GeometryType ParsedArgs::get_geometry_type() const
{
    return get_geometry_type_from_string(geometry_type);
}

MaterialType ParsedArgs::get_material_type() const
{
    return get_material_type_from_string(material_type);
}

GeometryType ParsedArgs::get_geometry_type_from_string(const std::string &type) const
{
    if (type == "Simple")
    {
        return GeometryType ::Simple;
    }
    else if (type == "Cube")
    {
        return GeometryType::Cube;
    }
    else
    {
        return GeometryType::InvalidType;
    }
}

MaterialType ParsedArgs::get_material_type_from_string(const std::string &type) const
{
    if (type == "Simple")
    {
        return MaterialType::Simple;
    }
    else
    {
        return MaterialType::InvalidType;
    }
}
