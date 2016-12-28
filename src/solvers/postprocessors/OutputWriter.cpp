#include <deal.II/lac/vector.h>
#include <deal.II/numerics/data_out.h>
#include <boost/filesystem/path.hpp>
#include <fstream>
#include "OutputWriter.hpp"

using namespace dealii;

OutputWriter::OutputWriter(const std::string &output_dir,
                           const std::string solution_name)
    :
    output_dir(output_dir),
    solution_name(solution_name)
{

}

void OutputWriter::do_postprocess(const dealii::DoFHandler<3> &dof_handler,
                                  const dealii::Vector<double> &solution)
{
    std::cout << "    Output solution..." << std::endl;

    DataOut<3> data_out;

    data_out.attach_dof_handler(dof_handler);
    data_out.add_data_vector(solution, solution_name);

    data_out.build_patches();

    boost::filesystem::path output_filename = output_dir;
    output_filename /= "solution.vtu";

    std::ofstream out(output_filename.c_str());

    data_out.write_vtu(out);
}
