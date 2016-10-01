#ifndef SHELL_PROBLEM_GEOMETRIES_HPP
#define SHELL_PROBLEM_GEOMETRIES_HPP

#include <deal.II/base/parameter_handler.h>

namespace Geometry
{

struct SimpleGeometry
{
    double inner_radius;
    double outer_radius;
    double cylinder_length;

    int n_global_refinements;

    static void declare_parameters(dealii::ParameterHandler &prm);
    void get_parameters(dealii::ParameterHandler &prm);
};

}

#endif //SHELL_PROBLEM_GEOMETRIES_HPP
