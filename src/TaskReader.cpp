#include "TaskReader.hpp"

using namespace TaskReader;
using namespace dealii;

ParametersParser::ParametersParser(const boost::filesystem::path &input_file)
{
    declare_parameters(parameter_handler);

    parameter_handler.read_input(input_file.c_str());

    parse_parameters(parameter_handler);
}

void ParametersParser::declare_parameters(dealii::ParameterHandler &prm)
{
    geometry.declare_parameters(prm);
    elasticity.declare_parameters(prm);
    heat.declare_parameters(prm);
}

void ParametersParser::parse_parameters(dealii::ParameterHandler &prm)
{
    geometry.parse_parameters(prm);
    elasticity.parse_parameters(prm);
    heat.parse_parameters(prm);
}


void GeometryProperties::declare_parameters(ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        prm.declare_entry("Geo file", "",
                          Patterns::FileName(),
                          "Path to .geo file with grid");
        prm.declare_entry("Msh file", "",
                          Patterns::FileName(),
                          "Path to .msh file with mesh");
    }
    prm.leave_subsection();
}

void GeometryProperties::parse_parameters(ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        geo_file = prm.get("Geo file");
        msh_file = prm.get("Msh file");
    }
    prm.leave_subsection();
}


void ElasticityProperties::declare_parameters(dealii::ParameterHandler &/*prm*/)
{

}

void ElasticityProperties::parse_parameters(dealii::ParameterHandler &/*prm*/)
{

}


void HeatProperties::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Heat");
    {
        prm.declare_entry("Thermal diffusivity", "9.0e-2",
                          Patterns::Double(0),
                          "Thermal diffusivity");

        prm.enter_subsection("Fairing boundary function");
        {
            fairing_boundary_function.declare_parameters(prm, 1);
        }
        prm.leave_subsection();

        prm.enter_subsection("Outer boundary function");
        {
            other_boundary_function.declare_parameters(prm, 1);
        }
        prm.leave_subsection();

        prm.enter_subsection("Right hand side function");
        {
            rhs_function.declare_parameters(prm, 1);
        }
        prm.leave_subsection();
    }
    prm.leave_subsection();
}

void HeatProperties::parse_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Heat");
    {
        a_square = prm.get_double("Thermal diffusivity");

        prm.enter_subsection("Fairing boundary function");
        {
            fairing_boundary_function.parse_parameters(prm);
        }
        prm.leave_subsection();

        prm.enter_subsection("Outer boundary function");
        {
            other_boundary_function.parse_parameters(prm);
        }
        prm.leave_subsection();

        prm.enter_subsection("Right hand side function");
        {
            rhs_function.parse_parameters(prm);
        }
        prm.leave_subsection();
    }
    prm.leave_subsection();
}
