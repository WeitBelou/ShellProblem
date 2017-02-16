#include "LayeredIsland.hpp"
#include <src/shell/util/MeshUtilities.hpp>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/manifold.h>
#include <deal.II/grid/manifold_lib.h>

using namespace dealii;
using namespace MeshUtilities;

LayeredIsland::LayeredIsland(const double layer_height,
                             const dealii::Point<3> &force_position,
                             const double island_radius,
                             const double force_radius,
                             const double height,
                             unsigned int n_global_refinements)
    :
    GeneratedMesh(n_global_refinements),
    layer_height(layer_height),
    force_position(force_position),
    island_radius(island_radius),
    force_radius(force_radius),
    height(height)
{
    create();
}

void LayeredIsland::create_coarse_mesh()
{
    Point<3> p1{-island_radius, -island_radius, -height / 2};
    Point<3> p2{island_radius, island_radius, height / 2};

    const unsigned n_cells_on_length = 5;

    const unsigned n_horizontal_reps = static_cast<unsigned>(n_cells_on_length * island_radius / force_radius);
    const unsigned n_vertical_reps = static_cast<unsigned>(n_cells_on_length * height / layer_height);
    const std::vector<unsigned> repetitions{n_horizontal_reps, n_horizontal_reps, n_vertical_reps};

    GridGenerator::subdivided_hyper_rectangle(tria, repetitions, p1, p2);
}

void LayeredIsland::apply_manifold_ids()
{
    static CylindricalManifold<3> force_position_manifold{dealii::Point<3>{0, 0, 0}, force_position};
    static FlatManifold<3> flat_manifold{};

    tria.set_manifold(0, flat_manifold);
    tria.set_manifold(1, force_position_manifold);

    tria.set_all_manifold_ids(0);

    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < GeometryInfo<3>::faces_per_cell; ++f) {
            auto face = cell->face(f);
            if (face->at_boundary()) {
                if (is_face_in_circle(face, force_position, force_radius, 2)) {
                    cell->set_all_manifold_ids(1);
                    break;
                }
            }
        }
    }
}

void LayeredIsland::apply_boundary_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < GeometryInfo<3>::faces_per_cell; ++f) {
            auto face = cell->face(f);
            if (face->at_boundary()) {
                if (face->manifold_id() == 1) {
                    face->set_all_boundary_ids(1);
                }
                else if (is_face_on_plane(face, dealii::Point<3>{0, 0, -height / 2}, 2)) {
                    face->set_all_boundary_ids(2);
                }
            }
        }
    }
}

void LayeredIsland::apply_material_ids()
{
    for (auto cell: tria.active_cell_iterators()) {
        cell->set_material_id(1);
    }
    const double z_0 = -height / 2;
    const double d = (height - n_layers * layer_height) / (n_layers + 1);
    for (unsigned layer = 0; layer < n_layers; ++layer) {
        const Point<3> down_border{0, 0, z_0 + (layer + 1) * d + layer_height * layer};
        const Point<3> upper_border = down_border + Point<3>{0, 0, layer_height};

        for (auto cell: tria.active_cell_iterators()) {
            if (is_cell_between_two_planes(cell, down_border, upper_border, 2)) {
                cell->set_material_id(2);
            }
        }
    }
}
