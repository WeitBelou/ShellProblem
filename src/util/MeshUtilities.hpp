#ifndef SHELL_PROBLEM_MESH_UTILITIES_HPP
#define SHELL_PROBLEM_MESH_UTILITIES_HPP
#include "deal.II/grid/tria.h"

class MeshUtilities
{
public:
    static bool is_point_on_sphere(const dealii::Point<3> &point,
                                   const dealii::Point<3> &center,
                                   const double radius);

    static bool is_point_on_plane(const dealii::Point<3> &point,
                                  const dealii::Point<3> &point_on_plane,
                                  const unsigned int axis);

    static bool is_face_on_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                                  const dealii::Point<3> &center,
                                  const double radius);

    static bool is_face_on_half_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                                       const dealii::Point<3> &center,
                                       const double radius,
                                       const dealii::Point<3> &orientation);

    static bool is_face_on_plane(const dealii::Triangulation<3>::active_face_iterator &face,
                                 const dealii::Point<3> &point_on_plane,
                                 const unsigned int axis);

    static bool is_face_in_circle(dealii::Triangulation<3, 3>::active_face_iterator face,
                                  const dealii::Point<3> &center,
                                  const double radius,
                                  const unsigned int axis);
private:
    static bool fuzzy_equal(const double x, const double y);
    static dealii::Point<3> get_axis_from_number(const unsigned int axis_no);
    static bool is_point_in_sphere(const dealii::Point<3> point, const dealii::Point<3> &center, const double radius);
    static bool is_point_on_half_sphere(const dealii::Point<3> point,
                                        const dealii::Point<3> &center,
                                        const double radius,
                                        const dealii::Point<3> &orientation);
};

#endif //SHELL_PROBLEM_MESH_UTILITIES_HPP
