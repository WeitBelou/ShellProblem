#include "Geometry.hpp"

using namespace dealii;

void Geometry::SimpleGeometry::declare_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        prm.enter_subsection("Sizes");
        {
            prm.declare_entry("Inner radius", "5.0",
                              Patterns::Double(0),
                              "Inner radius of the shell");
            prm.declare_entry("Outer radius", "5.3",
                              Patterns::Double(0),
                              "Outer radius of the shell");
            prm.declare_entry("Cylinder length", "5.0",
                              Patterns::Double(0),
                              "Length of shell\'s cylindrical part");
        }
        prm.leave_subsection();

        prm.declare_entry("N global refinements", "0",
                          Patterns::Integer(0, 6),
                          "Number of initial global refinements");
    }
    prm.leave_subsection();
}

void Geometry::SimpleGeometry::get_parameters(dealii::ParameterHandler &prm)
{
    prm.enter_subsection("Geometry");
    {
        prm.enter_subsection("Sizes");
        {
            inner_radius = prm.get_double("Inner radius");
            outer_radius = prm.get_double("Outer radius");
            cylinder_length = prm.get_double("Cylinder length");
        }
        prm.leave_subsection();

        n_global_refinements = prm.get_integer("N global refinements");
    }
    prm.leave_subsection();
}
