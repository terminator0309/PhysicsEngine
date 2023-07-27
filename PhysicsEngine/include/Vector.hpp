#pragma once

#include <cmath>

namespace pe{

    // custom vector for physics engine that supports int and float
    template<typename T>
    struct Vector{
        T _x;
        T _y;

        static Vector ORIGIN;

        Vector() :_x(0), _y(0) {};
        Vector(T val) : _x(val), _y(val) {};
        Vector(T x, T y) : _x(x), _y(y) {};

        Vector& operator=(const Vector& copy) {
            _x = copy._x;
            _y = copy._y;

            return *this;
        }

        // Assuming x at index 0 and y at index 1
        T get(int i) {
            if (i == 0) return _x;
            else return _y;
        }

        void set(int i, T val) {
            if (i == 0) _x = val;
            else _y = val;
        }

        Vector operator+(const Vector& other) const {
            return Vector(_x + other._x, _y + other._y);
        }

        Vector operator-(const Vector& other) const {
            return Vector(_x - other._x, _y - other._y);
        }

        Vector operator*(const Vector& other) const {
            return Vector(_x * other._x, _y * other._y);
        }

        Vector operator/(const Vector& other) const {
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

        Vector operator-() {
            return Vector(-_x, -_y);
        }

        void operator+=(const Vector& other) {
            _x += other._x;
            _y += other._y;
        }

        bool operator==(const Vector& other) const {
            return _x == other._x and _y == other._y;
        }

        bool operator==(Vector& other);

        T getSquare() {
            return _x * _x + _y * _y;
        }

        T dot(Vector other) {
            return _x * other._x + _y * other._y;
        }

        Vector normalize() {
            return (*this / std::sqrt(this->getSquare()));
        }

        float length() {
            return std::sqrt(this->getSquare());
        }
    };

    typedef Vector<int> Vector2i;
    typedef Vector<float> Vector2f;

    Vector2f Vector2f::ORIGIN = Vector2f();
    Vector2i Vector2i::ORIGIN = Vector2i();

}