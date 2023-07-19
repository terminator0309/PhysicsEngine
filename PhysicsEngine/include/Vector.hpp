#pragma once

namespace pe{

    // custom vector for physics engine that supports int and float
    template<typename T>
    struct Vector{
        T _x;
        T _y;

        Vector() :_x(0), _y(0) {};
        Vector(T val) : _x(val), _y(val) {};
        Vector(T x, T y) : _x(x), _y(y) {};

        Vector& operator=(const Vector& copy) {
            _x = copy._x;
            _y = copy._y;

            return *this;
        }

        Vector operator+(const Vector& other) {
            return Vector(_x + other._x, _y + other._y);
        }

        Vector operator-(const Vector& other) {
            return Vector(_x - other._x, _y - other._y);
        }

        Vector operator*(const Vector& other) {
            return Vector(_x * other._x, _y * other._y);
        }

        Vector operator/(const Vector& other) {
            return Vector(_x / other._x, _y / other._y);
        }

        Vector operator*(const T& val) {
            return Vector(_x * val, _y * val);
        }

        Vector operator/(const T& val) {
            return Vector(_x / val, _y / val);
        }

        Vector operator-(const T& val) {
            return Vector(_x - val, _y - val);
        }

        void operator+=(const Vector& other) {
            _x += other._x;
            _y += other._y;
        }

    };

    typedef Vector<int> Vector2i;
    typedef Vector<float> Vector2f;
}