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
        prm.declare_entry("N refinements", "",
                          Patterns::Integer(0, 10),
                          "N initial global refinements");

        prm.enter_subsection("Sizes");
        {
            prm.declare_entry("Inner radius", "5.0",
                              Patterns::Double(0.0),
                              "Inner radius");
            prm.declare_entry("Outer radius", "5.3",
                              Patterns::Double(0.0),
                              "Outer radius");
            prm.declare_entry("Cylinder length", "15.0",
                              Patterns::Double(0.0),
                              "Cylinder length");
        }
        prm.leave_subsection();
    }
    prm.leave_subsection();
}

void GeometryProperties::parse_parameters(ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        n_refinements = prm.get_integer("N refinemnts");

        prm.enter_subsection("Sizes");
        {
            inner_radius = prm.get_double("Inner radius");
            outer_radius = prm.get_double("Outer radius");
            cylinder_length = prm.get_double("Cylinder length");
        }
        prm.leave_subsection();
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
