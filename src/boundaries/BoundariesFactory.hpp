#ifndef SHELL_PROBLEM_BOUNDARIES_FACTORY_HPP
#define SHELL_PROBLEM_BOUNDARIES_FACTORY_HPP


#include <memory>
#include <deal.II/lac/solver_gmres.h>
#include <src/boundaries/BoundariesMap.hpp>
#include "src/task/TaskUtil.hpp"

class BoundariesFactory
{
public:
    static BoundariesMap create_boundaries(const json &boundaries_properties);
};


#endif //SHELL_PROBLEM_BOUNDARIES_FACTORY_HPP
