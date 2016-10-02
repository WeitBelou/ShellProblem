#ifndef SHELL_PROBLEM_TASK_READER_HPP
#define SHELL_PROBLEM_TASK_READER_HPP

#include <boost/filesystem/path.hpp>
#include <deal.II/base/parameter_handler.h>

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
    void initialize(GeometryType geometry, MaterialType material);
    void run(const boost::filesystem::path &input_file,
             const boost::filesystem::path &output_dir);
private:
    void declare_geometry(const GeometryType &geometry);
    void declare_material(const MaterialType &material);

    dealii::ParameterHandler parameter_handler;
    GeometryType geometry;
    MaterialType material;
};

}

#endif //SHELL_PROBLEM_TASK_READER_HPP
