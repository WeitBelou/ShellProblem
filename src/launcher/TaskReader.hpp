#ifndef SHELL_PROBLEM_TASK_READER_HPP
#define SHELL_PROBLEM_TASK_READER_HPP

#include <boost/filesystem/path.hpp>
#include <deal.II/base/parameter_handler.h>
#include <boost/program_options.hpp>

#include "mesh/MeshWrappers.hpp"
#include "SimpleMaterial.hpp"

namespace TaskReader
{

enum class GeometryType
{
    Simple, Cube, InvalidType
};

enum class MaterialType
{
    Simple, InvalidType
};

class Launcher
{
public:
    void initialize(const std::string &input_file);
    void run(const std::string &output_dir);
private:
    void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);

    GeometryType get_geometry_type_from_string(const std::string &type) const;
    MaterialType get_material_type_from_string(const std::string &type) const;

    GeometryType geometry;
    std::string path_to_geometry;

    MaterialType material;
    std::string path_to_material;
};

}

#endif //SHELL_PROBLEM_TASK_READER_HPP
