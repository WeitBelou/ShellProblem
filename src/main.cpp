#include <iostream>
#include <boost/program_options.hpp>

#include "src/TaskReader/TaskReader.hpp"

namespace po = boost::program_options;
using namespace TaskReader;

GeometryType get_geometry_type_from_string(const std::string & type)
{
    if (type == "Simple")
    {
        return GeometryType ::Simple;
    }
    else
    {
        return GeometryType::InvalidType;
    }
}
MaterialType get_material_type_from_string(const std::string & type)
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

int main(int argc, char **argv)
{
    po::options_description desc("Options");

    std::string task_file;
    std::string output_dir;

    std::string geometry_type;
    std::string material_type;

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

    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            return 0;
        }

        po::notify(vm);
    }
    catch (std::exception &exc)
    {
        std::cerr << "Error during parsing command line: " << std::endl
                  << exc.what() << std::endl;
        return 1;
    }

    Launcher launcher;
    launcher.initialize(get_geometry_type_from_string(geometry_type),
                        get_material_type_from_string(material_type));
    launcher.run(task_file, output_dir);

    return 0;
}
