#pragma once

#include <cmath>
#include <format>
#include <ostream>

#include "Constvals.h"

template<typename T>
class Tuple;

template<typename T>
class Tuple {
public:
    T x;
    T y;
    T z;
    T w;
public:
    Tuple(const T& x, const T& y, const T& z, const T& w)
    : x{x}
    , y{y}
    , z{z}
    , w{w}
    {
    }

    auto operator==(const Tuple<T>& rhs) const -> bool {
        return
            std::abs(this->x - rhs.x) < EPSILON &&
            std::abs(this->y - rhs.y) < EPSILON &&
            std::abs(this->z - rhs.z) < EPSILON &&
            std::abs(this->w - rhs.w) < EPSILON;
    }

    auto operator+(const Tuple<T>& rhs) const -> Tuple<T> {
        return {
            this->x + rhs.x,
            this->y + rhs.y,
            this->z + rhs.z,
            this->w + rhs.w
        };
    }

    auto operator+=(const Tuple<T>& rhs) -> Tuple<T>& {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        this->w += rhs.w;
        return *this;
    }

    auto operator-(const Tuple<T>& rhs) const -> Tuple<T> {
        return {
            this->x - rhs.x,
            this->y - rhs.y,
            this->z - rhs.z,
            this->w - rhs.w
        };
    }

    auto operator-=(const Tuple<T>& rhs) -> Tuple<T> {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        this->w -= rhs.w;
        return *this;
    }

    auto operator-() const -> Tuple<T> {
        return {
            0 - this->x,
            0 - this->y,
            0 - this->z,
            0 - this->w
        };
    }

    auto operator*(const T& scalar) const -> Tuple<T> {
        return {
            this->x * scalar,
            this->y * scalar,
            this->z * scalar,
            this->w * scalar
        };
    }

    auto operator/(const T& scalar) const -> Tuple<T> {
        return {
            this->x / scalar,
            this->y / scalar,
            this->z / scalar,
            this->w / scalar
        };
    }

    auto Magnitude() const -> T {
        return std::sqrt(x*x + y*y + z*z + w*w);
    }

    auto Normalize() const -> Tuple<T> {
        const T mag{Magnitude()};
        return {
            this->x / mag,
            this->y / mag,
            this->z / mag,
            this->w / mag
        };
    }

    auto Dot(const Tuple<T>& tup) const -> T {
        return {
            this->x * tup.x +
            this->y * tup.y +
            this->z * tup.z +
            this->w * tup.w
        };
    }



};
using TupleF = Tuple<float>;

template<typename T>
auto operator<<(std::ostream& ostream, const Tuple<T>& tup) -> std::ostream&;
template<typename T = float>
auto operator<<(std::ostream& os, const TupleF& tup) -> std::ostream& {
    os << std::format("({},{},{},{})", tup.x, tup.y, tup.z, tup.w);
    return os;
}

template<typename T>
auto operator*(const T& scalar, const Tuple<T>& tup) -> Tuple<T> {
    return tup*scalar;
}

template<typename T>
auto Magnitude(const Tuple<T>& tup) -> T {
    return tup.Magnitude();
}

template<typename T>
auto Normalize(const Tuple<T>& tup) -> Tuple<T> {
    return tup.Normalize();
}

template<typename T>
auto Dot(const Tuple<T>& lhs, const Tuple<T>& rhs) -> T {
    return lhs.Dot(rhs);
}


template<typename T>
auto Cross(const Tuple<T>& lhs, const Tuple<T>& rhs) -> Tuple<T> {
    return lhs.Cross(rhs);
}


template<typename T>
auto Point(const T& x, const T& y, const T& z) -> Tuple<T>;
template<typename T = float>
auto Point(const float& x, const float& y, const float& z) -> TupleF {
    return TupleF{x, y, z, 1.0};
}
auto PointF(const float& x, const float& y, const float& z) -> TupleF;

template<typename T>
auto Vector_t(const T& x, const T& y, const T& z) -> Tuple<T>;
template<typename T = float>
auto Vector_t(const float& x, const float& y, const float& z) -> TupleF {
    return TupleF{x, y, z, 0.0};
}
auto VectorF(const float& x, const float& y, const float& z) -> TupleF;
