#pragma once
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/lac/vector.h>

class Postprocessor
{
public:
    virtual void do_postprocess(const dealii::DoFHandler<3> &dof_handler,
                                const dealii::Vector<double> &solution) = 0;
};