#pragma once

#include "Vector.h"

class Tuple : public Vector4f {
public:
    Tuple(const float& x, const float& y, const float& z, const float& w)
    : Vector4f{{x,y,z,w}}
    , x{Vector4f::operator()(0)}
    , y{Vector4f::operator()(1)}
    , z{Vector4f::operator()(2)}
    , w{Vector4f::operator()(3)}
    {}
    Tuple(const Vector4f& vec)
    : Vector4f{vec}
    , x{Vector4f::operator()(0)}
    , y{Vector4f::operator()(1)}
    , z{Vector4f::operator()(2)}
    , w{Vector4f::operator()(3)}
    {}
    Tuple(const Tuple& tup)
    : Vector4f{tup}
    , x{Vector4f::operator()(0)}
    , y{Vector4f::operator()(1)}
    , z{Vector4f::operator()(2)}
    , w{Vector4f::operator()(3)}
    {}

    auto operator=(const Tuple& rhs) -> Tuple& {
        x = Vector4f::operator()(0);
        y = Vector4f::operator()(1);
        z = Vector4f::operator()(2);
        w = Vector4f::operator()(3);
    }

    auto Cross(const Tuple& tup) const -> Tuple {
        return {
            this->y * tup.z - this->z * tup.y,
            this->z * tup.x - this->x * tup.z,
            this->x * tup.y - this->y * tup.x,
            0.f
        };
    }
    float& x;
    float& y;
    float& z;
    float& w;
};

namespace Factory {

auto Point(const float& x, const float& y, const float& z) -> Tuple;
auto Vector(const float& x, const float& y, const float& z) -> Tuple;

}
