#include "MshMesh.hpp"

#include <deal.II/grid/grid_in.h>
#include <fstream>
#include <deal.II/base/logstream.h>
MshMesh::MshMesh(const std::string &grid_file_name, const MeshMarkersGroup &markers)
{
    dealii::GridIn<3> grid_in;
    grid_in.attach_triangulation(tria);

    std::ifstream grid_file(grid_file_name);
    grid_in.read_msh(grid_file);

    for (auto cell: tria.active_cell_iterators()) {
        for (unsigned f = 0; f < dealii::GeometryInfo<3>::faces_per_cell; ++f) {
            if (cell->face(f)->at_boundary()) {
                cell->face(f)->set_all_boundary_ids(0);
            }
        }
        cell->set_material_id(0);
    }

    markers.apply_markers(tria);
}
