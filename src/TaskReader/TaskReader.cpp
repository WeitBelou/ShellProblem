#include <iostream>
#include "TaskReader.hpp"

#include "mesh/MeshWrappers.hpp"
#include "solvers/HeatSolver.hpp"
#include "solvers/ElasticitySolver.hpp"

using namespace dealii;

using namespace TaskReader;

using namespace Material;
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
    this->geometry = geometry;
    switch (geometry)
    {
        case GeometryType::Simple:
            SimpleShellMesh::declare_parameters(parameter_handler);
            break;
        case GeometryType::Cube:
            CubeMesh::declare_parameters(parameter_handler);
            break;
        case GeometryType::InvalidType:
        AssertThrow(false, ExcInternalError("You are trying to initialize "
                                                "launcher with invalid geometry type."));
    }
}

void Launcher::run(const boost::filesystem::path &input_file,
                   const boost::filesystem::path &output_dir)
{
    parameter_handler.parse_input(input_file.c_str());

    if (geometry == GeometryType::Simple)
    {
        MeshWrappers::SimpleShellMesh shell_mesh(parameter_handler);

        if (material == MaterialType::Simple)
        {
            SimpleMaterial simple_material;
            simple_material.get_parameters(parameter_handler);

            HeatSolver::SimpleSolver heat_solver(shell_mesh,
                                                 simple_material.heat);
            heat_solver.run(output_dir);

        }
    }
    else if (geometry == GeometryType::Cube)
    {
        CubeMesh cube_mesh(parameter_handler);

        if (material == MaterialType::Simple)
        {
            SimpleMaterial simple_material;
            simple_material.get_parameters(parameter_handler);

            HeatSolver::SimpleSolver heat_solver(cube_mesh,
                                                 simple_material.heat);
            heat_solver.run(output_dir);

        }
    }
}
