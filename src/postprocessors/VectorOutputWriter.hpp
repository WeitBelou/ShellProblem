#pragma once
#include "Postprocessor.hpp"
class VectorOutputWriter: public Postprocessor
{
public:
    void do_postprocess(const dealii::DoFHandler<3> &dof_handler,
                        const dealii::Vector<double> &solution) override;
private:
    const std::string output_dir;
    const std::string solution_name;
public:
    VectorOutputWriter(const std::string &output_dir, const std::string &solution_name);
};
