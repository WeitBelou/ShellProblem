#ifndef SHELL_PROBLEM_TASK_READER_HPP
#define SHELL_PROBLEM_TASK_READER_HPP

#include <boost/filesystem/path.hpp>

#include <deal.II/base/parameter_handler.h>
#include <deal.II/base/parsed_function.h>

namespace TaskReader
{

struct GeometryProperties
{
    double inner_radius;
    double outer_radius;
    double cylinder_length;

    int n_refinements;

    void declare_parameters(dealii::ParameterHandler &prm);
    void parse_parameters(dealii::ParameterHandler &prm);
};

struct ElasticityProperties
{


    void declare_parameters(dealii::ParameterHandler &prm);
    void parse_parameters(dealii::ParameterHandler &prm);
};

struct HeatProperties
{
    double a_square;

    dealii::Functions::ParsedFunction<3> fairing_boundary_function;
    dealii::Functions::ParsedFunction<3> other_boundary_function;
    dealii::Functions::ParsedFunction<3> rhs_function;

    void declare_parameters(dealii::ParameterHandler &prm);
    void parse_parameters(dealii::ParameterHandler &prm);
};

class ParametersParser
{
public:
    ParametersParser(const boost::filesystem::path &input_file);

    GeometryProperties geometry;
    ElasticityProperties elasticity;
    HeatProperties heat;

private:
    void declare_parameters(dealii::ParameterHandler &prm);
    void parse_parameters(dealii::ParameterHandler &prm);

    dealii::ParameterHandler parameter_handler;
};

}

#endif //SHELL_PROBLEM_TASK_READER_HPP
