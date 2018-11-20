#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <math.h>

template <class T>
class Vector2 {

    public:
        T x, y;

    Vector2() {}
    Vector2(T x, T y) { this->x = x; this->y = y; }

    Vector2<T> operator+(const Vector2<T>& vec1)
    {
        return Vector2<T>(this->x + vec1.x, this->y + vec1.y);
    }

    T operator*(const Vector2<T>& vec1)
    {
        return this->x * vec1.x + this->y * vec1.y;
    }

    Vector2<T> operator*(const double mult)
    {
        return Vector2<T>(this->x * mult, this->y * mult);
    }

    Vector2<T> operator/(const double mult)
    {
        return Vector2<T>(this->x / mult, this->y / mult);
    }

    double length()
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    void normalize()
    {
        double length = this->length();
        this->x /= length;
        this->y /= length;
    }
};

typedef Vector2<double> Vector2f;
typedef Vector2<int> Vector2i;

#endif // VECTOR_H_INCLUDED
