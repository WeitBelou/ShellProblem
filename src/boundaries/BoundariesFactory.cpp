#include "BoundariesFactory.hpp"
#include "Boundaries.hpp"

BoundariesGroup BoundariesFactory::create_boundaries(const json &boundaries_properties)
{
    BoundariesGroup boundaries;
    create_dirichlet_boundaries(boundaries_properties["dirichlet"], boundaries);
    create_neumann_boundaries(boundaries_properties["neumann"], boundaries);
    return boundaries;
}

void BoundariesFactory::create_dirichlet_boundaries(const json &drichlet_properties, BoundariesGroup &boundaries)
{
    for (const json & boundary: drichlet_properties) {
        const dealii::types::boundary_id id = boundary["id"].get<dealii::types::boundary_id>();
        const std::string type = boundary["type"].get<std::string>();
        if (type == "sin_square") {
            boundaries.add_dirichlet(id, std::make_shared<SinSquare>(boundary["amplitude"].get<double>()));
        }
        else if (type == "constant") {
            boundaries.add_dirichlet(id, std::make_shared<dealii::ConstantFunction<3>>(boundary["value"].get<double>()));
        }
        else {
            AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented())
        }
    }
}

void BoundariesFactory::create_neumann_boundaries(const json &neumann_properties, BoundariesGroup &boundaries)
{
    for (const json & boundary: neumann_properties) {
        const dealii::types::boundary_id id = boundary["id"].get<dealii::types::boundary_id>();
        const std::string type = boundary["type"].get<std::string>();
        if (type == "sin_square") {
            boundaries.add_neumann(id, std::make_shared<SinSquare>(boundary["amplitude"].get<double>()));
        }
        else if (type == "constant") {
            boundaries.add_neumann(id, std::make_shared<dealii::ConstantFunction<3>>(boundary["value"].get<double>()));
        }
        else {
            AssertThrow(false, dealii::StandardExceptions::ExcNotImplemented())
        }
    }
}
