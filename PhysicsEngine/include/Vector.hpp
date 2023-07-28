#pragma once

#include <cmath>

namespace pe{

    // custom vector for physics engine that supports int and float
    template<typename T>
    struct Vector{
        T x;
        T y;

        static Vector ORIGIN;

        Vector() :x(0), y(0) {};
        Vector(T val) : x(val), y(val) {};
        Vector(T x, T y) : x(x), y(y) {};

        Vector& operator=(const Vector& copy) {
            x = copy.x;
            y = copy.y;

            return *this;
        }

        // Assuming x at index 0 and y at index 1
        T get(int i) {
            if (i == 0) return x;
            else return y;
        }

        void set(int i, T val) {
            if (i == 0) x = val;
            else y = val;
        }

        Vector operator+(const Vector& other) const {
            return Vector(x + other.x, y + other.y);
        }

        Vector operator-(const Vector& other) const {
            return Vector(x - other.x, y - other.y);
        }

        Vector operator*(const Vector& other) const {
            return Vector(x * other.x, y * other.y);
        }

        Vector operator/(const Vector& other) const {
            return Vector(x / other.x, y / other.y);
        }

        Vector operator*(const T& val) {
            return Vector(x * val, y * val);
        }

        Vector operator/(const T& val) {
            return Vector(x / val, y / val);
        }

        Vector operator-(const T& val) {
            return Vector(x - val, y - val);
        }

        Vector operator-() {
            return Vector(-x, -y);
        }

        void operator+=(const Vector& other) {
            x += other.x;
            y += other.y;
        }

        bool operator==(const Vector& other) const {
            return x == other.x and y == other.y;
        }

        bool operator==(Vector& other);

        T getSquare() {
            return x * x + y * y;
        }

        T dot(Vector other) {
            return x * other.x + y * other.y;
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