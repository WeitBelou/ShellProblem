#pragma once
#include <deal.II/numerics/data_out.h>
class OutputWriter
{
public:
    OutputWriter(const dealii::DoFHandler<3> &dof_handler);

    void add_scalar_data(const dealii::Vector<double> &solution,
                         const std::string &solution_name);
    void add_vector_data(const dealii::Vector<double> &solution,
                         const std::string &solution_name);
    void add_matrix_data(const std::vector<std::vector<dealii::Vector<double>>> &matrix,
                         const std::string &solution_name);

    void write_results(const std::string &output_dir,
                       const std::string &file_name);
private:
    dealii::DataOut<3> data_out;

    const dealii::DoFHandler<3> &dof_handler;
};
