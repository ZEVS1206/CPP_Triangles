#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <vector>

#include "triangles.hpp"

template<typename T>
static T orient_2D(const Point_2D<T>& P, const Point_2D<T>& Q, const Point_2D<T>& R);
template<typename T>
static bool on_segment(const Point_2D<T>& P, const Point_2D<T>& Q, const Point_2D<T>& R);
template<typename T>
static bool segments_intersect(const Point_2D<T>& A, const Point_2D<T>& B, const Point_2D<T>& C, const Point_2D<T>& D);
template<typename T>
static T triangle_area2D(const Point_2D<T>& A, const Point_2D<T>& B, const Point_2D<T>& C);
template<typename T>
static bool point_in_triangle(const Point_2D<T>& P, const Point_2D<T>& A, const Point_2D<T>& B, const Point_2D<T>& C);

template <typename T>
T project_onto_line(const Vector_3<T>& vec, const Vector_3<T>& line_vector)
{
    T len = line_vector.len_of_vector();
    Vector_3<T> normal_line_vector = {line_vector.get_x()/len, line_vector.get_y()/len, line_vector.get_z()/len};
    return scalar_multiply(vec, normal_line_vector);
}

template<typename T>
static T orient_2D(const Point_2D<T>& P, const Point_2D<T>& Q, const Point_2D<T>& R) 
{
    return (Q.get_x() - P.get_x()) * (R.get_y() - P.get_y()) - 
           (Q.get_y() - P.get_y()) * (R.get_x() - P.get_x());
}

template<typename T>
static bool on_segment(const Point_2D<T>& P, const Point_2D<T>& Q, const Point_2D<T>& R)
{
    return Q.get_x() >= std::min(P.get_x(), R.get_x()) && Q.get_x() <= std::max(P.get_x(), R.get_x()) &&
           Q.get_y() >= std::min(P.get_y(), R.get_y()) && Q.get_y() <= std::max(P.get_y(), R.get_y());
}

template<typename T>
static bool segments_intersect(const Point_2D<T>& A, const Point_2D<T>& B, const Point_2D<T>& C, const Point_2D<T>& D)
{
    T o1 = orient_2D(A, B, C);
    T o2 = orient_2D(A, B, D);
    T o3 = orient_2D(C, D, A);
    T o4 = orient_2D(C, D, B);

    if (o1 * o2 < 0 && o3 * o4 < 0) 
    {
        return true;
    }

    if (o1 == 0 && on_segment(A, C, B)) 
    {
        return true;
    }
    if (o2 == 0 && on_segment(A, D, B)) 
    {
        return true;
    }
    if (o3 == 0 && on_segment(C, A, D)) 
    {
        return true;
    }
    if (o4 == 0 && on_segment(C, B, D)) 
    {
        return true;
    }

    return false;
}

template <typename T>
static T triangle_area2D(const Point_2D<T>& A, const Point_2D<T>& B, const Point_2D<T>& C)
{
    T area2 = A.get_x() * (B.get_y() - C.get_y()) + B.get_x() * (C.get_y() - A.get_y()) + C.get_x() * (A.get_y() - B.get_y());
    return std::abs(area2) * T(0.5);
}

template<typename T>
static bool point_in_triangle(const Point_2D<T>& P, const Point_2D<T>& A, const Point_2D<T>& B, const Point_2D<T>& C)
{
    T eps = std::numeric_limits<T>::epsilon();
    T S  = triangle_area2D(A, B, C);
    T S1 = triangle_area2D(P, B, C);
    T S2 = triangle_area2D(A, P, C);
    T S3 = triangle_area2D(A, B, P);

    return std::abs(S - (S1 + S2 + S3)) < eps;
}

template <typename T>
bool triangles_intersection_complanar(Triangle<T>& triangle_1, Triangle<T>& triangle_2)
{
    T normal_1_x = ((triangle_1.plane_of_triangle).normal_).get_x();
    T normal_1_y = ((triangle_1.plane_of_triangle).normal_).get_y();
    T normal_1_z = ((triangle_1.plane_of_triangle).normal_).get_z();
    std::vector <T> normal = {normal_1_x, normal_1_y, normal_1_z};
    T max_component = *std::max_element(normal.begin(), normal.end());
    int proj_plane = 0;//proj_plane = 0 - project onto YZ, proj_plane = 1 - project onto XZ, proj_plane = 2 - project onto XY
    if (max_component == normal_1_y)
    {
        proj_plane = 1;
    }
    else if (max_component == normal_1_z)
    {
        proj_plane = 2;
    }
    Point_2D<T> A1;
    Point_2D<T> B1;
    Point_2D<T> C1;
    Point_2D<T> A2;
    Point_2D<T> B2;
    Point_2D<T> C2;


    if (proj_plane == 0)
    {
        A1.set_x((triangle_1.get_a()).get_y());
        A1.set_y((triangle_1.get_a()).get_z());
        B1.set_x((triangle_1.get_b()).get_y());
        B1.set_y((triangle_1.get_b()).get_z());
        C1.set_x((triangle_1.get_c()).get_y());
        C1.set_y((triangle_1.get_c()).get_z());
        A2.set_x((triangle_2.get_a()).get_y());
        A2.set_y((triangle_2.get_a()).get_z());
        B2.set_x((triangle_2.get_b()).get_y());
        B2.set_y((triangle_2.get_b()).get_z());
        C2.set_x((triangle_2.get_c()).get_y());
        C2.set_y((triangle_2.get_c()).get_z());
    }
    else if (proj_plane == 1)
    {
        A1.set_x((triangle_1.get_a()).get_x());
        A1.set_y((triangle_1.get_a()).get_z());
        B1.set_x((triangle_1.get_b()).get_x());
        B1.set_y((triangle_1.get_b()).get_z());
        C1.set_x((triangle_1.get_c()).get_x());
        C1.set_y((triangle_1.get_c()).get_z());
        A2.set_x((triangle_2.get_a()).get_x());
        A2.set_y((triangle_2.get_a()).get_z());
        B2.set_x((triangle_2.get_b()).get_x());
        B2.set_y((triangle_2.get_b()).get_z());
        C2.set_x((triangle_2.get_c()).get_x());
        C2.set_y((triangle_2.get_c()).get_z());
    }
    else if (proj_plane == 2)
    {
        A1.set_x((triangle_1.get_a()).get_x());
        A1.set_y((triangle_1.get_a()).get_y());
        B1.set_x((triangle_1.get_b()).get_x());
        B1.set_y((triangle_1.get_b()).get_y());
        C1.set_x((triangle_1.get_c()).get_x());
        C1.set_y((triangle_1.get_c()).get_y());
        A2.set_x((triangle_2.get_a()).get_x());
        A2.set_y((triangle_2.get_a()).get_y());
        B2.set_x((triangle_2.get_b()).get_x());
        B2.set_y((triangle_2.get_b()).get_y());
        C2.set_x((triangle_2.get_c()).get_x());
        C2.set_y((triangle_2.get_c()).get_y());
    }

    bool is_segment_intersection = segments_intersect(A1, B1, A2, B2) || segments_intersect(A1, B1, B2, C2) ||
                                   segments_intersect(A1, B1, A2, C2) || segments_intersect(B1, C1, A2, B2) || 
                                   segments_intersect(B1, C1, B2, C2) || segments_intersect(B1, C1, A2, C2) ||
                                   segments_intersect(A1, C1, A2, B2) || segments_intersect(A1, C1, B2, C2) ||
                                   segments_intersect(A1, C1, A2, C2);
    if (is_segment_intersection)
    {
        return is_segment_intersection;
    }

    bool is_point_in_triangle = point_in_triangle(A2, A1, B1, C1) || point_in_triangle(B2, A1, B1, C1) ||
                                point_in_triangle(C2, A1, B1, C1) || point_in_triangle(A1, A2, B2, C2) ||
                                point_in_triangle(B1, A2, B2, C2) || point_in_triangle(C1, A2, B2, C2);
    return is_point_in_triangle;
}

template <typename T>
bool triangles_intersection(Triangle<T>& triangle_1, Triangle<T>& triangle_2)
{
    triangle_1.get_plane_of_triangle();
    triangle_2.get_plane_of_triangle();

    Vector_3<T> OA1((triangle_1.get_a()).get_x(), (triangle_1.get_a()).get_y(), (triangle_1.get_a()).get_z());
    Vector_3<T> OB1((triangle_1.get_b()).get_x(), (triangle_1.get_b()).get_y(), (triangle_1.get_b()).get_z());
    Vector_3<T> OC1((triangle_1.get_c()).get_x(), (triangle_1.get_c()).get_y(), (triangle_1.get_c()).get_z());
    Vector_3<T> OA2((triangle_2.get_a()).get_x(), (triangle_2.get_a()).get_y(), (triangle_2.get_a()).get_z());
    Vector_3<T> OB2((triangle_2.get_b()).get_x(), (triangle_2.get_b()).get_y(), (triangle_2.get_b()).get_z());
    Vector_3<T> OC2((triangle_2.get_c()).get_x(), (triangle_2.get_c()).get_y(), (triangle_2.get_c()).get_z());
    triangle_1.set_OA(OA1);
    triangle_1.set_OB(OB1);
    triangle_1.set_OC(OC1);
    triangle_2.set_OA(OA2);
    triangle_2.set_OB(OB2);
    triangle_2.set_OC(OC2);
    T dist_vec2_0 = scalar_multiply((triangle_1.plane_of_triangle).normal_, OA2) + (triangle_1.plane_of_triangle).D_;
    T dist_vec2_1 = scalar_multiply((triangle_1.plane_of_triangle).normal_, OB2) + (triangle_1.plane_of_triangle).D_;
    T dist_vec2_2 = scalar_multiply((triangle_1.plane_of_triangle).normal_, OC2) + (triangle_1.plane_of_triangle).D_;

    if (dist_vec2_0 > 0 && dist_vec2_1 > 0 && dist_vec2_2 > 0)
    {
        return false;
    }
    if (dist_vec2_0 < 0 && dist_vec2_1 < 0 && dist_vec2_2 < 0)
    {
        return false;
    }

    T dist_vec1_0 = scalar_multiply((triangle_2.plane_of_triangle).normal_, OA1) + (triangle_2.plane_of_triangle).D_;
    T dist_vec1_1 = scalar_multiply((triangle_2.plane_of_triangle).normal_, OB1) + (triangle_2.plane_of_triangle).D_;
    T dist_vec1_2 = scalar_multiply((triangle_2.plane_of_triangle).normal_, OC1) + (triangle_2.plane_of_triangle).D_;

    if (dist_vec1_0 > 0 && dist_vec1_1 > 0 && dist_vec1_2 > 0)
    {
        return false;
    }
    if (dist_vec1_0 < 0 && dist_vec1_1 < 0 && dist_vec1_2 < 0)
    {
        return false;
    }

    Vector_3<T> line_vector = vector_multiply((triangle_1.plane_of_triangle).normal_, (triangle_2.plane_of_triangle).normal_);
    
    const T eps = std::numeric_limits<T>::epsilon();

    if (line_vector.len_of_vector() < eps)
    {
        return triangles_intersection_complanar(triangle_1, triangle_2);
    }

    T t1_min = 0;
    T t1_max = 0;
    T t2_min = 0;
    T t2_max = 0;

    T proj_1_0 = project_onto_line(OA1, line_vector);
    T proj_1_1 = project_onto_line(OB1, line_vector);
    T proj_1_2 = project_onto_line(OC1, line_vector);

    std::vector<T> projections_1 = {proj_1_0, proj_1_1, proj_1_2};

    t1_min = *std::min_element(projections_1.begin(), projections_1.end());
    t1_max = *std::max_element(projections_1.begin(), projections_1.end());

    T proj_2_0 = project_onto_line(OA2, line_vector);
    T proj_2_1 = project_onto_line(OB2, line_vector);
    T proj_2_2 = project_onto_line(OC2, line_vector);

    std::vector<T> projections_2 = {proj_2_0, proj_2_1, proj_2_2};

    t2_min = *std::min_element(projections_2.begin(), projections_2.end());
    t2_max = *std::max_element(projections_2.begin(), projections_2.end());

    if (t1_max < t2_min || t2_max < t1_min)
    {
        return false;
    }
    return true;
}

int main()
{
    Point_t<double> point_A1;
    Point_t<double> point_B1;
    Point_t<double> point_C1;
    Point_t<double> point_A2;
    Point_t<double> point_B2;
    Point_t<double> point_C2;

    std::cin >> point_A1 >> point_B1 >> point_C1;
    std::cin >> point_A2 >> point_B2 >> point_C2;

    // Vector_3<double> vector_1_1(point_B1.get_x() - point_A1.get_x(), point_B1.get_y() - point_A1.get_y(), point_B1.get_z() - point_A1.get_z());
    // Vector_3<double> vector_2_1(point_C1.get_x() - point_B1.get_x(), point_C1.get_y() - point_B1.get_y(), point_C1.get_z() - point_B1.get_z());
    // Vector_3<double> vector_3_1(point_A1.get_x() - point_C1.get_x(), point_A1.get_y() - point_C1.get_y(), point_A1.get_z() - point_C1.get_z());
    // Vector_3<double> vector_1_2(point_B2.get_x() - point_A2.get_x(), point_B2.get_y() - point_A2.get_y(), point_B2.get_z() - point_A2.get_z());
    // Vector_3<double> vector_2_2(point_C2.get_x() - point_B2.get_x(), point_C2.get_y() - point_B2.get_y(), point_C2.get_z() - point_B2.get_z());
    // Vector_3<double> vector_3_2(point_A2.get_x() - point_C2.get_x(), point_A2.get_y() - point_C2.get_y(), point_A2.get_z() - point_C2.get_z());


    Triangle<double> tr_1(point_A1, point_B1, point_C1);
    Triangle<double> tr_2(point_A2, point_B2, point_C2);

    bool answer = triangles_intersection(tr_1, tr_2);
    std::cout << std::boolalpha << answer << "\n";
    
    return 0;
}