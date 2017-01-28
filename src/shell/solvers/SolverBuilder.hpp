#pragma once
#include <memory>
#include "src/shell/util/JsonUtil.hpp"

#include "src/shell/linear_solver/LinearSolverBase.hpp"
#include "src/shell/boundaries/BoundariesGroup.hpp"
#include "src/shell/materials/MaterialsGroup.hpp"
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
