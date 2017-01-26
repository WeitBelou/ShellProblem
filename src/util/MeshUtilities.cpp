#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_reordering.h>
#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/grid_generator.h>

#include "MeshUtilities.hpp"

using namespace dealii;

bool
MeshUtilities::is_point_in_sphere(const dealii::Point<3> point,
                                  const dealii::Point<3> &center,
                                  const double radius)
{
    return ((point - center).norm() < radius) || is_point_on_sphere(point, center, radius);
}

bool MeshUtilities::is_point_on_sphere(const dealii::Point<3> &point,
                                       const dealii::Point<3> &center,
                                       const double radius)
{
    return fuzzy_equal((point - center).norm(), radius);
}

bool MeshUtilities::is_point_on_plane(const dealii::Point<3> &point,
                                      const dealii::Point<3> &point_on_plane,
                                      const unsigned int axis)
{
    //Plane: (n, r) == (n, r_0)
    const dealii::Point<3> axis_vector = get_axis_from_number(axis);
    return fuzzy_equal(point * axis_vector, point_on_plane * axis_vector);

}

bool MeshUtilities::is_face_on_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                                      const dealii::Point<3> &center,
                                      const double radius)
{
    for (unsigned int v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!is_point_on_sphere(current_point, center, radius)) {
            return false;
        }
    }
    return true;
}

bool MeshUtilities::is_face_on_plane(const dealii::Triangulation<3>::active_face_iterator &face,
                                     const dealii::Point<3> &point_on_plane,
                                     const unsigned int axis)
{
    for (unsigned int v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!is_point_on_plane(current_point, point_on_plane, axis)) {
            return false;
        }
    }
    return true;
}

dealii::Point<3> MeshUtilities::get_axis_from_number(const unsigned int axis_no)
{
    switch (axis_no) {
        case 0:
            return dealii::Point<3>(1, 0, 0);
        case 1:
            return dealii::Point<3>(0, 1, 0);
        case 2:
            return dealii::Point<3>(0, 0, 1);
        default: AssertThrow(false, dealii::StandardExceptions::ExcIndexRange(axis_no, 0, 3));
    }
    return dealii::Point<3>();
}

bool MeshUtilities::fuzzy_equal(const double x, const double y)
{
    return std::fabs(x - y) < std::numeric_limits<double>::round_error();
}

bool MeshUtilities::is_face_in_circle(dealii::Triangulation<3, 3>::active_face_iterator face,
                                      const dealii::Point<3> &center,
                                      const double radius,
                                      const unsigned int axis)
{
    if (!is_face_on_plane(face, center, axis)) {
        return false;
    }

    for (unsigned int v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!is_point_in_sphere(current_point, center, radius)) {
            return false;
        }
    }

    return true;
}

bool MeshUtilities::is_face_on_half_sphere(const Triangulation<3, 3>::active_face_iterator &face,
                                           const Point<3> &center,
                                           const double radius,
                                           const Point<3> &orientation)
{
    for (unsigned int v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!is_point_on_half_sphere(current_point, center, radius, orientation)) {
            return false;
        }
    }

    return true;
}

bool MeshUtilities::is_point_on_half_sphere(const Point<3> point,
                                            const Point<3> &center,
                                            const double radius,
                                            const Point<3> &orientation)
{
    if (!is_point_on_sphere(point, center, radius)) {
        return false;
    }
    if ((point - center) * orientation < 0) {
        return false;
    }

    return true;
}

bool MeshUtilities::is_cell_between_two_planes(Triangulation<3, 3>::active_cell_iterator cell,
                                               const Point<3> point_on_first_plane,
                                               const Point<3> point_on_second_plane,
                                               const unsigned int axis)
{
    for (unsigned v = 0; v < GeometryInfo<3>::vertices_per_cell; ++v) {
        if (!is_point_between_two_planes(cell->vertex(v), point_on_first_plane, point_on_second_plane, axis)) {
            return false;
        }
    }
    return true;
}

bool MeshUtilities::is_point_between_two_planes(const dealii::Point<3> point,
                                                const dealii::Point<3> point_on_first_plane,
                                                const dealii::Point<3> point_on_second_plane,
                                                unsigned axis)
{
    return (point_on_first_plane(axis) <= point(axis)) && (point(axis) <= point_on_second_plane(axis));
}
