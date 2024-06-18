#pragma once

#include "Constvals.h"

#include <array>
#include <cassert>
#include <ranges>
#include <cmath>

using uint = unsigned int;

template<typename T, std::size_t N>
class Vector_t {
protected:
    std::array<T, N> arr;

public:
    Vector_t()
    : arr{}
    {}
    Vector_t(const std::array<T, N>& list)
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

    auto operator==(const Vector_t<T, N>& rhs) const -> bool {
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            if (std::abs(val-rhs(i)) >= EPSILON) {
                return false;
            }
        }
        return true;
    }

    auto operator+(const Vector_t<T, N>& rhs) const -> Vector_t<T, N> {
        Vector_t<T, N> buffer;
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            buffer(i) = val + rhs(i);
        }
        return buffer;
    }

    auto operator-(const Vector_t<T, N>& rhs) const -> Vector_t<T, N> {
        Vector_t<T, N> buffer;
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            buffer(i) = val - rhs(i);
        }
        return buffer;
    }

    auto operator-() const -> Vector_t<T, N> {
        Vector_t<T, N> buffer;
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            buffer(i) = 0.f - val;
        }
        return buffer;
    }

    auto operator*(const T& rhs) const -> Vector_t<T, N> {
        Vector_t<T, N> buffer;
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            buffer(i) = val*rhs;
        }
        return buffer;
    }

    auto operator/(const T& rhs) const -> Vector_t<T, N> {
        Vector_t<T, N> buffer;
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            buffer(i) = val/rhs;
        }
        return buffer;
    }

    auto Magnitude() const -> T {
        return std::sqrt(this->Dot(*this));
    }

    auto Normalize() const -> Vector_t<T, N> {
        const T mag{Magnitude()};
        return *this/mag;
    }

    auto Dot(const Vector_t<T, N>& vec) const -> T {
        T accumulate{0};
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            accumulate += val*vec(i);
        }
        return accumulate;
    }

};

using Vector2f = Vector_t<double, 2>;
using Vector3f = Vector_t<double, 3>;
using Vector4f = Vector_t<double, 4>;

template<typename T, std::size_t N>
auto Dot(const Vector_t<T, N>& vec1, const Vector_t<T, N>& vec2) -> T {
    return vec1.Dot(vec2);
}

#include <iostream>

template<typename T, std::size_t N>
auto operator<<(std::ostream& os, Vector_t<T, N> vec) -> std::ostream& {
    for (uint i=0; i<N; ++i) {
        os << vec(i) << ' ';
    }
    return os;
}