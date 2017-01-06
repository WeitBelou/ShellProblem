#ifndef SHELLPROBLEM_SOLVERBUILDER_HPP
#define SHELLPROBLEM_SOLVERBUILDER_HPP

#include <memory>

#include "src/linear_solver/LinearSolverBase.hpp"
#include "src/boundaries/BoundariesGroup.hpp"
#include "src/util/JsonUtil.hpp"
#include "SolverBase.hpp"

class SolverBuilder
{

public:
    static std::shared_ptr<SolverBase> create_solver(const json &solver_properties,
                                                     std::shared_ptr<MeshBase> mesh,
                                                     std::shared_ptr<LinearSolverBase> linear_solver,
                                                     BoundariesGroup boundaries);
};


#endif //SHELLPROBLEM_SOLVERBUILDER_HPP
