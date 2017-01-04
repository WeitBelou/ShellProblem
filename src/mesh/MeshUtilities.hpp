#ifndef SHELL_PROBLEM_MESH_UTILITIES_HPP
#define SHELL_PROBLEM_MESH_UTILITIES_HPP
#include "deal.II/grid/tria.h"

class MeshUtilities
{
public:
    static bool is_point_on_sphere(const dealii::Point<3> &point,
                                   const dealii::Point<3> &center,
                                   const double radius,
                                   const double tolerance = 1e-10);

    static bool is_point_on_plane(const dealii::Point<3> &point,
                                  const dealii::Point<3> &point_on_plane,
                                  const unsigned int axis,
                                  const double tolerance = 1e-10);

    static bool is_point_on_circle(const dealii::Point<3> &point,
                                   const dealii::Point<3> &center,
                                   const double radius,
                                   const unsigned int axis,
                                   const double tolerance = 1e-10);

    static bool is_face_on_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                                  const dealii::Point<3> &center,
                                  const double radius,
                                  const double tolerance = 1e-10);

    static bool is_face_on_plane(const dealii::Triangulation<3>::active_face_iterator &face,
                                 const dealii::Point<3> &point_on_plane,
                                 const unsigned int axis,
                                 const double tolerance = 1e-10);

    static bool is_face_inscribed_in_circle(const dealii::Triangulation<3>::active_face_iterator &face,
                                            const dealii::Point<3> &center,
                                            const double radius,
                                            const unsigned int axis,
                                            const double tolerance = 1e-10);

    static bool is_face_on_cylinder(const dealii::Triangulation<3>::active_face_iterator &face,
                                    const dealii::Point<3> &center,
                                    const unsigned int axis,
                                    const double radius,
                                    const double length,
                                    const double tolerance = 1e-10);
private:
    static bool fuzzy_equal(const double x, const double y, const double tolerance);
    static dealii::Point<3> get_axis_from_number(const unsigned int axis_no);
};

#endif //SHELL_PROBLEM_MESH_UTILITIES_HPP
