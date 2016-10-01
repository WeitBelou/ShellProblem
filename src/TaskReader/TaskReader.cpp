#include <iostream>
#include "TaskReader.hpp"

#include "mesh/MeshWrappers.hpp"
#include "solvers/HeatSolver.hpp"
#include "solvers/ElasticitySolver.hpp"

using namespace dealii;

using namespace TaskReader;

using namespace Material;
using namespace Geometry;
using namespace MeshWrappers;

void Launcher::initialize(GeometryType geometry, MaterialType material)
{
    declare_geometry(geometry);
    declare_material(material);

}

void Launcher::declare_material(const MaterialType &material)
{
    AssertThrow(material != MaterialType::InvalidType,
                ExcInternalError("You are trying to initialize launcher"
                                     " with invalid material type."))


    if (material == MaterialType::Simple)
    {
        SimpleMaterial::declare_parameters(parameter_handler);
        this->material = material;
    }
}

void Launcher::declare_geometry(const GeometryType &geometry)
{
    AssertThrow(geometry != GeometryType::InvalidType,
                ExcInternalError("You are trying to initialize "
                                     "launcher with invalid geometry type."))
    if (geometry == GeometryType::Simple)
    {
        SimpleGeometry::declare_parameters(parameter_handler);
        this->geometry = geometry;
    }
}

void Launcher::run(const boost::filesystem::path &input_file,
                   const boost::filesystem::path &output_dir)
{
    parameter_handler.read_input(input_file.c_str());

    if (geometry == GeometryType::Simple)
    {
        SimpleGeometry simple_geometry;
        simple_geometry.get_parameters(parameter_handler);

        MeshWrappers::SimpleShellMesh shell_mesh(simple_geometry);

        if (material == MaterialType::Simple)
        {
            SimpleMaterial simple_material;
            simple_material.get_parameters(parameter_handler);

            HeatSolver::SimpleSolver heat_solver(shell_mesh,
                                                 simple_material.heat);
            heat_solver.run(output_dir);

        }
    }
}
