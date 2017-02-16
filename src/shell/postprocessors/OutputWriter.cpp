#include <fstream>
#include <boost/filesystem/path.hpp>

#include <deal.II/lac/vector.h>
#include <deal.II/numerics/data_out.h>

#include "OutputWriter.hpp"

using namespace dealii;

OutputWriter::OutputWriter(const DoFHandler<3> &dof_handler)
    :
    dof_handler(dof_handler)
{
    data_out.attach_dof_handler(dof_handler);
}

void OutputWriter::add_scalar_data(const dealii::Vector<double> &solution,
                                   const std::string &solution_name)
{
    data_out.add_data_vector(solution, solution_name);
}

void OutputWriter::add_vector_data(const dealii::Vector<double> &solution,
                                   const std::string &solution_name)
{
    std::vector<std::string> solution_names(3, solution_name);

    std::vector<DataComponentInterpretation::DataComponentInterpretation>
        data_component_interpretation
        (3, DataComponentInterpretation::component_is_part_of_vector);

    data_out.add_data_vector(solution, solution_names,
                             DataOut<3>::type_dof_data,
                             data_component_interpretation);
}

void OutputWriter::add_matrix_data(const std::vector<std::vector<dealii::Vector<double>>> &matrix,
                                   const std::string &solution_name)
{
    for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            data_out.add_data_vector(matrix[i][j], solution_name + "_" + std::to_string(i) + std::to_string(j));
        }
    }
}

void OutputWriter::write_results(const std::string &output_dir,
                                 const std::string &file_name)
{
    data_out.build_patches();

    boost::filesystem::path output_filename = output_dir;
    output_filename /= (file_name + ".vtu");

    std::ofstream out(output_filename.c_str());

    data_out.write_vtu(out);
}
