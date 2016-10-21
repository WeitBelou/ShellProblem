#include "ElasticitySolver.hpp"

Solvers::ElasticitySolver::ElasticitySolver(const MeshWrappers::Mesh &mesh,
                                             const Material::SimpleElasticity &elasticity)
{

}

void Solvers::ElasticitySolver::run(const boost::filesystem::path &output_dir)
{
    std::cout << "    Solve..." << std::endl;
    std::cout << "    Solved." << std::endl;
}
