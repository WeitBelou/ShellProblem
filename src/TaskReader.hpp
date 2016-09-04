#ifndef SHELL_PROBLEM_TASK_READER_HPP
#define SHELL_PROBLEM_TASK_READER_HPP

#include <boost/filesystem/path.hpp>

#include <deal.II/base/parameter_handler.h>

namespace TaskReader
{

struct GeometryProperties
{
    double L;
    double r;
    double d;

    int n_global_refinements;

    static void declare_parameters(dealii::ParameterHandler &prm);
    void parse_parameters(dealii::ParameterHandler &prm);
};

struct ElasticityProperties
{


    static void declare_parameters(dealii::ParameterHandler &prm);
    void parse_parameters(dealii::ParameterHandler &prm);
};

struct HeatProperties
{


    static void declare_parameters(dealii::ParameterHandler &prm);
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
    static void declare_parameters(dealii::ParameterHandler &prm);
    void parse_parameters(dealii::ParameterHandler &prm);

    dealii::ParameterHandler parameter_handler;
};

}

#endif //SHELL_PROBLEM_TASK_READER_HPP