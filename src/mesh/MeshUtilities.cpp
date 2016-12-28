#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_reordering.h>
#include <deal.II/grid/grid_in.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/grid_generator.h>

#include "MeshUtilities.hpp"

using namespace MeshUtilities;


bool MeshUtilities::is_point_on_sphere(const dealii::Point<3> &point,
                                       const dealii::Point<3> &center,
                                       const double radius,
                                       const double tolerance)
{
    return fuzzy_equal((point - center).norm(), radius, tolerance);
}

bool MeshUtilities::is_point_on_plane(const dealii::Point<3> &point,
                                      const dealii::Point<3> &point_on_plane,
                                      const size_t axis,
                                      const double tolerance)
{
    //Plane: (n, r) == (n, r_0)
    const dealii::Point<3> axis_vector = get_axis_from_number(axis);
    return fuzzy_equal(point * axis_vector, point_on_plane * axis_vector, tolerance);

}

bool MeshUtilities::is_point_on_circle(const dealii::Point<3> &point,
                                       const dealii::Point<3> &center,
                                       const double radius,
                                       const size_t axis,
                                       const double tolerance)
{
    if (!is_point_on_plane(point, center, axis, tolerance)) {
        return false;
    }
    return is_point_on_sphere(point, center, radius, tolerance);

}

bool MeshUtilities::is_face_on_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                                      const dealii::Point<3> &center,
                                      const double radius,
                                      const double tolerance)
{
    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!is_point_on_sphere(current_point, center, radius, tolerance)) {
            return false;
        }
    }
    return true;
}

bool MeshUtilities::is_face_on_plane(const dealii::Triangulation<3>::active_face_iterator &face,
                                     const dealii::Point<3> &point_on_plane,
                                     const size_t axis,
                                     const double tolerance)
{
    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!is_point_on_plane(current_point, point_on_plane, axis, tolerance)) {
            return false;
        }
    }
    return true;
}

bool MeshUtilities::is_face_inscribed_in_circle(const dealii::Triangulation<3>::active_face_iterator &face,
                                                const dealii::Point<3> &center,
                                                const double radius,
                                                const size_t axis,
                                                const double tolerance)
{
    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> current_point = face->vertex(v);
        if (!is_point_on_circle(current_point, center, radius, axis, tolerance)) {
            return false;
        }
    }
    return true;
}

bool MeshUtilities::is_face_on_cylinder(const dealii::Triangulation<3>::active_face_iterator &face,
                                        const dealii::Point<3> &center,
                                        const size_t axis,
                                        const double radius,
                                        const double length,
                                        const double tolerance)
{
    dealii::Point<3> axis_vector = get_axis_from_number(axis);

    for (size_t v = 0; v < dealii::GeometryInfo<3>::vertices_per_face; ++v) {
        const dealii::Point<3> shifted_vertex = face->vertex(v) + (-center);
        const double distance_to_axis = (shifted_vertex - (axis_vector * shifted_vertex) * axis_vector).norm();

        if (!fuzzy_equal(distance_to_axis, radius, tolerance)) {
            return false;
        }
        else if (shifted_vertex(axis) > length / 2 || shifted_vertex(axis) < -length / 2) {
            return false;
        }
    }
    return true;
}

dealii::Point<3> MeshUtilities::get_axis_from_number(size_t axis_no)
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

bool MeshUtilities::fuzzy_equal(const double x, const double y, const double tolerance)
{
    return std::fabs(x - y) < tolerance;
}
