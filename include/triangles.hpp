#ifndef TRIANGLES_HPP
#define TRIANGLES_HPP

#include <iostream>
#include <cmath>

template <typename T>
class Point_t
{
private:
    T x_;
    T y_;
    T z_;
public:
    Point_t (): x_(0), y_(0), z_(0){}
    Point_t (T x, T y, T z): x_(x), y_(y), z_(z) {}
    T get_x() const
    {
        return x_;
    }
    T get_y() const
    {
        return y_;
    }
    T get_z() const
    {
        return z_;
    }
    
    void set_x(T x)
    {
        x_ = x;
        return;
    }
    void set_y(T y)
    {
        y_ = y;
        return;
    }
    void set_z(T z)
    {
        z_ = z;
        return;
    }
    friend std::istream& operator >> (std::istream& is, Point_t<T>& point)
    {
        T x = 0;
        T y = 0;
        T z = 0;
        is >> x >> y >> z;
        point.set_x(x);
        point.set_y(y);
        point.set_z(z);
        return is;
    }

    Point_t<T>& operator =(const Point_t<T>& point)
    {
        if (this == &point)
        {
            return *this;
        }
        this->set_x(point.get_x());
        this->set_y(point.get_y());
        this->set_z(point.get_z());
        return *this;
    }
    ~Point_t() {}
};

template <typename T>
class Vector_3
{
private:
    T x_;
    T y_;
    T z_;
public:
    Vector_3(): x_(0), y_(0), z_(0) {}
    Vector_3(T x, T y, T z): x_(x), y_(y), z_(z){}
    T get_x() const
    {
        return x_;
    }
    T get_y() const
    {
        return y_;
    }
    T get_z() const
    {
        return z_;
    }

    void set_x(T x)
    {
        x_ = x;
        return;
    }
    void set_y(T y)
    {
        y_ = y;
        return;
    }
    void set_z(T z)
    {
        z_ = z;
        return;
    }

    T len_of_vector() const
    {
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    Vector_3<T> operator +(const Vector_3<T>& vec)
    {
        return Vector_3<T>(x_ + vec.get_x(), y_ + vec.get_y(), z_ + vec.get_z());
    }

    Vector_3<T> operator -(const Vector_3<T>& vec)
    {
        return Vector_3<T>(x_ - vec.get_x(), y_ - vec.get_y(), z_ - vec.get_z());
    }

    Vector_3<T> operator *(const T scalar)
    {
        return Vector_3<T>(x_ * scalar, y_ * scalar, z_ * scalar);
    }

    Vector_3<T>& operator =(const Vector_3<T>& vec)
    {
        if (this == &vec)
        {
            return *this;
        }
        this->set_x(vec.get_x());
        this->set_y(vec.get_y());
        this->set_z(vec.get_z());
        return *this;
    }
    friend std::istream& operator >>(std::istream& is, Vector_3<T>& vec)
    {
        T x_1 = 0;
        T x_2 = 0;
        T y_1 = 0;
        T y_2 = 0;
        T z_1 = 0;
        T z_2 = 0;
        is >> x_1 >> y_1 >> z_1 >> x_2 >> y_2 >> z_2;
        vec.set_x(x_2 - x_1);
        vec.set_y(y_2 - y_1);
        vec.set_z(z_2 - z_1);
        return is;
    }

    friend T scalar_multiply(const Vector_3<T>& vec_1, const Vector_3<T>& vec_2)
    {
        return (vec_1.get_x() * vec_2.get_x() + vec_1.get_y() * vec_2.get_y() + vec_1.get_z() * vec_2.get_z());
    }

    friend Vector_3<T> vector_multiply(const Vector_3<T>& vec_1, const Vector_3<T>& vec_2)
    {
        return Vector_3<T>(vec_1.get_y() * vec_2.get_z() - vec_1.get_z() * vec_2.get_y(),
                           vec_1.get_z() * vec_2.get_x() - vec_1.get_x() * vec_2.get_z(),
                           vec_1.get_x() * vec_2.get_y() - vec_1.get_y() * vec_2.get_x());
    }

    ~Vector_3() {}
};

template <typename T>
class Triangle
{
private:
    Point_t<T> a_;
    Point_t<T> b_;
    Point_t<T> c_;
    Vector_3<T> OA_;
    Vector_3<T> OB_;
    Vector_3<T> OC_;
public:
    struct Plane
    {
        Vector_3<T> normal_;
        T D_;
    };
    Plane plane_of_triangle;

    Triangle() {}
    Triangle(Point_t<T>& a, Point_t<T>& b, Point_t<T>& c): a_(a), b_(b), c_(c) {}
    Point_t<T> get_a() const
    {
        return a_;
    }
    Point_t<T> get_b() const
    {
        return b_;
    }
    Point_t<T> get_c() const
    {
        return c_;
    }

    Vector_3<T> get_OA() const
    {
        return OA_;
    }
    Vector_3<T> get_OB() const
    {
        return OB_;
    }
    Vector_3<T> get_OC() const
    {
        return OC_;
    }

    void set_a(const Point_t<T>& point)
    {
        a_ = point;
        return;
    }
    void set_b(const Point_t<T>& point)
    {
        b_ = point;
        return;
    }
    void set_c(const Point_t<T>& point)
    {
        c_ = point;
        return;
    }

    void set_OA(const Vector_3<T>& vec)
    {
        OA_ = vec;
        return;
    }
    void set_OB(const Vector_3<T>& vec)
    {
        OB_ = vec;
        return;
    }
    void set_OC(const Vector_3<T>& vec)
    {
        OC_ = vec;
        return;
    }

    void get_plane_of_triangle()
    {
        Vector_3<T> AB(b_.get_x() - a_.get_x(), b_.get_y() - a_.get_y(), b_.get_z() - a_.get_z());
        Vector_3<T> AC(c_.get_x() - a_.get_x(), c_.get_y() - a_.get_y(), c_.get_z() - a_.get_z());

        // normal = AB × AC
        plane_of_triangle.normal_ = vector_multiply(AB, AC);

        T len = plane_of_triangle.normal_.len_of_vector();
        if (len == T(0))
        {
            std::cerr << "Degenerate triangle\n";
            return;
        }

        plane_of_triangle.normal_.set_x(plane_of_triangle.normal_.get_x() / len);
        plane_of_triangle.normal_.set_y(plane_of_triangle.normal_.get_y() / len);
        plane_of_triangle.normal_.set_z(plane_of_triangle.normal_.get_z() / len);

        // D = - n · A
        Vector_3<T> A(a_.get_x(), a_.get_y(), a_.get_z());

        plane_of_triangle.D_ = -scalar_multiply(plane_of_triangle.normal_, A);
    }


    ~Triangle() {}
};

template<typename T>
class Point_2D 
{
private:
    T x_;
    T y_;
public:
    Point_2D() {}
    Point_2D(T x, T y): x_(x), y_(y) {}
    T get_x() const
    {
        return x_;
    }
    T get_y() const
    {
        return y_;
    }
    void set_x(T x)
    {
        x_ = x;
        return;
    }
    void set_y(T y)
    {
        y_ = y;
        return;
    }
    ~Point_2D() {}
};

template <typename T>
bool triangles_intersection(Triangle<T>& triangle_1, Triangle<T>& triangle_2);
template<typename T>
T project_onto_line(const Vector_3<T>& vec, const Vector_3<T>& line_vector);
template <typename T>
bool triangles_intersection_complanar(Triangle<T>& triangle_1, Triangle<T>& triangle_2);


#endif