#pragma once

#include "Constvals.h"

#include <array>
using uint = unsigned int;

template<typename T, std::size_t N>
class Vector {
    std::array<T, N> arr;

public:
    Vector()
    : arr{}
    {}
    Vector(std::array<T, N> list)
    : arr{list}
    {}


    auto operator()(const uint& index) -> T& {
        assert(index < N);
        return arr[index];
    }

    auto operator()(const uint& index) const -> const T& {
        assert(index < N);
        return arr[index];
    }

    auto operator==(const Vector<T, N>& rhs) const -> bool {
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            if (std::abs(val-rhs(i)) >= EPSILON) {
                return false;
            }
        }
        return true;
    }

    auto operator+(const Vector<T, N>& rhs) const -> Vector<T, N> {
        std::array<T, N> buffer;
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            buffer(i) = val + rhs(i);
        }
        return buffer;
    }

    auto operator-(const Vector<T, N>& rhs) const -> Vector<T, N> {
        std::array<T, N> buffer;
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            buffer(i) = val - rhs(i);
        }
        return buffer;
    }

    auto Magnitude() const -> T {
        return std::sqrt(this->Dot(*this));
    }

    auto Normalize() const -> Vector<T, N> {
        const T mag{Magnitude()};
        return {
            this->x / mag,
            this->y / mag,
            this->z / mag,
            this->w / mag
        };
    }

    auto Dot(const Vector<T, N>& vec) const -> T {
        T accumulate{0};
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            accumulate += val*vec(i);
        }
        return accumulate;
    }

};

using Vector2f = Vector<float, 2>;
using Vector3f = Vector<float, 3>;
using Vector4f = Vector<float, 4>;

template<typename T, std::size_t N>
auto Dot(const Vector<T, N>& vec1, const Vector<T, N>& vec2) -> T {
    return vec1.Dot(vec2);
}

#include <iostream>

template<typename T, std::size_t N>
auto operator<<(std::ostream& os, Vector<T, N> vec) -> std::ostream& {
    for (uint i=0; i<N; ++i) {
        os << vec(i) << ' ';
    }
    return os;
}