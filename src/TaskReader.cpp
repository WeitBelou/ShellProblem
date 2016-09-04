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
    GeometryProperties::declare_parameters(prm);
    ElasticityProperties::declare_parameters(prm);
    HeatProperties::declare_parameters(prm);
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
        prm.enter_subsection("Sizes");
        {
            prm.declare_entry("L", "15.0",
                              Patterns::Double(0.1),
                              "Length of the shell.");

            prm.declare_entry("r", "5.0",
                              Patterns::Double(0.1),
                              "Inner radius");

            prm.declare_entry("d", "0.3",
                              Patterns::Double(0.01),
                              "Thickness of the shell");
        }
        prm.leave_subsection();

        prm.declare_entry("N global refinements", "1",
                          Patterns::Integer(0, 5),
                          "Number of global refinements");
    }
    prm.leave_subsection();
}

void GeometryProperties::parse_parameters(ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        prm.enter_subsection("Sizes");
        {
            L = prm.get_double("L");
            r = prm.get_double("r");
            d = prm.get_double("d");
        }
        prm.leave_subsection();

        n_global_refinements = prm.get_integer("N global refinements");
    }
    prm.leave_subsection();
}


void ElasticityProperties::declare_parameters(dealii::ParameterHandler &/*prm*/)
{

}

void ElasticityProperties::parse_parameters(dealii::ParameterHandler &/*prm*/)
{

}


void HeatProperties::declare_parameters(dealii::ParameterHandler &/*prm*/)
{

}

void HeatProperties::parse_parameters(dealii::ParameterHandler &/*prm*/)
{

}
