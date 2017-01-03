#include "BoundariesFactory.hpp"
#include "Boundaries.hpp"

BoundariesMap BoundariesFactory::create_boundaries(const json &solver_properties)
{
    BoundariesMap boundaries;
    const json boundaries_array = solver_properties["boundaries"];
    for (json boundary: boundaries_array) {
        const dealii::types::boundary_id id = boundary["id"].get<dealii::types::boundary_id>();
        if (boundary["type"] == "sin_square") {
            boundaries.add_function(id, std::make_shared<SinSquare>(boundary["amplitude"].get<double>()));
        }
        else if (boundary["type"] == "constant") {
            boundaries.add_function(id, std::make_shared<dealii::ConstantFunction<3>>(boundary["value"].get<double>()));
        }
        else {
            AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented())
        }
    }
    return boundaries;
}