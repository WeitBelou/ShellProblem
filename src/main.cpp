#include <iostream>
#include <boost/program_options.hpp>

#include "TaskReader.hpp"
#include "MeshCreator.hpp"
#include "solvers/ElasticitySolver.hpp"
#include "solvers/HeatSolver.hpp"
#include "solvers/BoundaryConditions.hpp"

namespace po = boost::program_options;

int main(int argc, char **argv)
{
    po::options_description desc("Options");

    std::string task_file;
    std::string output_dir;
    std::string problem_type;

    auto task_file_option = po::value<std::string>(&task_file);
    task_file_option->value_name("task")->required();

    auto output_dir_option = po::value<std::string>(&output_dir);
    output_dir_option->value_name("output")->default_value("./");

    desc.add_options()
            ("help,H", "Show help")
            ("task,T", task_file_option, "File with task")
            ("output,O", output_dir_option, "Output directory");

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

    TaskReader::ParametersParser parameters(task_file);

    dealii::Triangulation<3> tria;
    MeshCreators::create_coarse_shell_mesh(tria, parameters.geometry);
    MeshCreators::write_msh(tria, "coarse.tmp.msh");

    try
    {
        HeatSolver::SimpleSolver
            solver(tria, parameters.heat);
        solver.run(output_dir);
    }
    catch (std::exception &exc)
    {
        std::cerr << "Error during solving elasticity problem"
                  << exc.what() << std::endl;
        return 1;
    }
    return 0;
}