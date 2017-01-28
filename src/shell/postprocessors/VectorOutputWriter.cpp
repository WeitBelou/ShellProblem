#include <fstream>
#include <boost/filesystem/path.hpp>

#include <deal.II/numerics/data_out.h>
#include "VectorOutputWriter.hpp"

using namespace dealii;

VectorOutputWriter::VectorOutputWriter(const std::string &output_dir,
                                       const std::string &solution_name)
    :
    output_dir(output_dir),
    solution_name(solution_name)
{}

void VectorOutputWriter::do_postprocess(const dealii::DoFHandler<3> &dof_handler,
                                        const dealii::Vector<double> &solution)
{
    boost::filesystem::path output_file_name = output_dir;
    output_file_name /= (solution_name + ".vtu");
    std::ofstream out(output_file_name.c_str());

    DataOut<3> data_out;
    data_out.attach_dof_handler(dof_handler);

    std::vector<std::string> solution_names(3, solution_name);

    std::vector<DataComponentInterpretation::DataComponentInterpretation>
        data_component_interpretation
        (3, DataComponentInterpretation::component_is_part_of_vector);

    data_out.add_data_vector(solution, solution_names,
                             DataOut<3>::type_dof_data,
                             data_component_interpretation);

    data_out.build_patches();

    data_out.write_vtu(out);
}
