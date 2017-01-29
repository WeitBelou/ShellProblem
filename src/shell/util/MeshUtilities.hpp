#pragma once
#include "deal.II/grid/tria.h"

namespace MeshUtilities
{
bool is_point_on_plane(const dealii::Point<3> &point,
                       const dealii::Point<3> &point_on_plane,
                       const unsigned int axis);

bool is_face_on_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                       const dealii::Point<3> &center,
                       const double radius);

bool is_face_on_half_sphere(const dealii::Triangulation<3>::active_face_iterator &face,
                            const dealii::Point<3> &center,
                            const double radius,
                            const dealii::Point<3> &orientation);

bool is_face_on_plane(const dealii::Triangulation<3>::active_face_iterator &face,
                      const dealii::Point<3> &point_on_plane,
                      const unsigned int axis);

bool is_face_in_circle(dealii::Triangulation<3, 3>::active_face_iterator face,
                       const dealii::Point<3> &center,
                       const double radius,
                       const unsigned int axis);

bool is_cell_between_two_planes(dealii::TriaActiveIterator<dealii::CellAccessor<3, 3>> cell,
                                const dealii::Point<3> point_on_first_plane,
                                const dealii::Point<3> point_on_second_plane,
                                const unsigned int axis);
bool is_point_on_sphere(const dealii::Point<3> &point,
                        const dealii::Point<3> &center,
                        const double radius);
bool is_point_in_sphere(const dealii::Point<3> point,
                        const dealii::Point<3> &center,
                        const double radius);
bool is_point_on_half_sphere(const dealii::Point<3> point,
                             const dealii::Point<3> &center,
                             const double radius,
                             const dealii::Point<3> &orientation);
bool is_point_between_two_planes(const dealii::Point<3> point,
                                 const dealii::Point<3> point_on_first_plane,
                                 const dealii::Point<3> point_on_second_plane,
                                 unsigned axis);

dealii::Point<3> get_axis_from_number(const unsigned int axis_no);
bool fuzzy_equal(const double x, const double y);
}
