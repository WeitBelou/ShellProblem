#ifndef SHELL_PROBLEM_MESH_UTILITIES_HPP
#define SHELL_PROBLEM_MESH_UTILITIES_HPP
#include "deal.II/grid/tria.h"

namespace MeshUtilities
{
bool is_point_on_sphere(const dealii::Point<3> &point,
                        const dealii::Point<3> &center,
                        const double radius,
                        const double tolerance = 1e-10);

bool is_point_on_plane(const dealii::Point<3> &point,
                       const dealii::Point<3> &point_on_plane,
                       const size_t axis,
                       const double tolerance = 1e-10);

bool is_point_on_circle(const dealii::Point<3> &point,
                        const dealii::Point<3> &center,
                        const double radius,
                        const size_t axis,
                        const double tolerance = 1e-10);

bool is_face_on_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                       const dealii::Point<3> &center,
                       const double radius,
                       const double tolerance = 1e-10);

bool is_face_on_plane(const dealii::Triangulation<3>::active_face_iterator &face,
                      const dealii::Point<3> &point_on_plane,
                      const size_t axis,
                      const double tolerance = 1e-10);

bool is_face_inscribed_in_circle(const dealii::Triangulation<3>::active_face_iterator &face,
                                 const dealii::Point<3> &center,
                                 const double radius,
                                 const size_t axis,
                                 const double tolerance = 1e-10);

bool is_face_on_cylinder(const dealii::Triangulation<3>::active_face_iterator &face,
                         const dealii::Point<3> &center,
                         const size_t axis,
                         const double radius,
                         const double length,
                         const double tolerance = 1e-10);

bool fuzzy_equal(const double x, const double y, const double tolerance);
dealii::Point<3> get_axis_from_number(size_t axis_no);
}

#endif //SHELL_PROBLEM_GENERAL_SOLVER_HPP
