#pragma once

#include <memory>

#include <deal.II/lac/solver_gmres.h>

#include "boundaries/BoundariesGroup.hpp"
#include "util/JsonUtil.hpp"

class BoundariesFactory
{
public:
    static BoundariesGroup create_boundaries(const json &boundaries_properties);
private:
    static void create_neumann_boundaries(const json &neumann_properties, BoundariesGroup &boundaries);
    static void create_dirichlet_boundaries(const json &drichlet_properties, BoundariesGroup &boundaries);
};
