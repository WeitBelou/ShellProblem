#ifndef SHELL_PROBLEM_LAUNCHER_HPP
#define SHELL_PROBLEM_LAUNCHER_HPP

#include <boost/filesystem/path.hpp>
#include <deal.II/base/parameter_handler.h>
#include <boost/program_options.hpp>
#include <src/launcher/task/TaskFactory.hpp>

#include "mesh/MeshWrappers.hpp"
#include "src/material/SimpleMaterial.hpp"

#include "task/TaskFactory.hpp"

namespace TaskReader
{

class Launcher
{
public:
    void run(const std::string &task_file, const std::string &output_dir);
};

}

#endif //SHELL_PROBLEM_LAUNCHER_HPP
