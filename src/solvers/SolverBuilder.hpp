#pragma once
#include <memory>
#include "util/JsonUtil.hpp"

#include "linear_solver/LinearSolverBase.hpp"
#include "boundaries/BoundariesGroup.hpp"
#include "materials/MaterialsGroup.hpp"
#include "SolverBase.hpp"

class SolverBuilder
{

public:
    static std::shared_ptr<SolverBase> create_solver(const json &solver_properties,
                                                     std::shared_ptr<MeshBase> mesh,
                                                     std::shared_ptr<LinearSolverBase> linear_solver,
                                                     BoundariesGroup boundaries,
                                                     MaterialsGroup materials);
};
