#ifndef SHELL_PROBLEM_BOUNDARIES_FACTORY_HPP
#define SHELL_PROBLEM_BOUNDARIES_FACTORY_HPP


#include <memory>
#include <deal.II/lac/solver_gmres.h>
#include <src/boundaries/BoundariesGroup.hpp>
#include "src/util/JsonUtil.hpp"

class BoundariesFactory
{
public:
    static BoundariesGroup create_boundaries(const json &boundaries_properties);
    static void create_neumann_boundaries(const json &neumann_properties, BoundariesGroup &boundaries);
    static void create_dirichlet_boundaries(const json &drichlet_properties, BoundariesGroup &boundaries);
};


#endif //SHELL_PROBLEM_BOUNDARIES_FACTORY_HPP
