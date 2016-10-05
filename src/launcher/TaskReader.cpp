#include "TaskReader.hpp"
#include <iostream>
#include <memory>

#include "solvers/HeatSolver.hpp"
#include "solvers/ElasticitySolver.hpp"

using namespace dealii;

using namespace TaskReader;

using namespace Material;
using namespace MeshWrappers;

void Launcher::run(const std::string &output_dir)
{
    std::unique_ptr<Mesh> mesh;
    switch (geometry)
    {
        case GeometryType::Simple:
            mesh = std::unique_ptr<Mesh>(new SimpleShellMesh);
            break;
        case GeometryType::Cube:
            mesh = std::unique_ptr<Mesh>(new CubeMesh);
            break;
        case GeometryType::InvalidType:
        AssertThrow(false, ExcInternalError("Invalid geometry type"));
            break;
    }
    mesh->initialize(path_to_geometry);

    if (material == MaterialType::Simple)
    {
        SimpleMaterial simple_material(path_to_material);
        HeatSolver::SimpleSolver heat_solver(*mesh, simple_material.get_heat());
        heat_solver.run(output_dir);
    }
    else
    {
        AssertThrow(false, ExcInternalError("Invalid material type"));
    }
}

void Launcher::initialize(const std::string &input_file)
{
    ParameterHandler prm;
    declare_parameters(prm);
    prm.parse_input(input_file);
    get_parameters(prm);
}

void Launcher::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Material");
    {
        prm.declare_entry("Type", "Simple",
                          Patterns::Selection("Simple"));
        prm.declare_entry("Path", "",
                          Patterns::FileName(),
                          "Path to file with material description");
    }
    prm.leave_subsection();

    prm.enter_subsection("Geometry");
    {
        prm.declare_entry("Type", "Simple",
                          Patterns::Selection("Simple|Cube"));
        prm.declare_entry("Path", "",
                          Patterns::FileName(),
                          "Path to file with geometry description");
    }
    prm.leave_subsection();
}

void Launcher::get_parameters(ParameterHandler &prm)
{
    prm.enter_subsection("Material");
    {
        material = get_material_type_from_string(prm.get("Type"));
        path_to_material = prm.get("Path");
    }
    prm.leave_subsection();

    prm.enter_subsection("Geometry");
    {
        geometry = get_geometry_type_from_string(prm.get("Type"));
        path_to_geometry = prm.get("Path");
    }
    prm.leave_subsection();
}
GeometryType Launcher::get_geometry_type_from_string(const std::string &type) const
{
    if (type == "Simple")
    {
        return GeometryType::Simple;
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
MaterialType Launcher::get_material_type_from_string(const std::string &type) const
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