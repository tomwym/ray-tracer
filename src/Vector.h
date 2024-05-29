#pragma once

#include "Tuple.h"

class Vector : public Tuple {
public:
    Vector(const float& x, const float& y, const float& z)
    : Tuple{x,y,z,0.f}
    {}

    Vector(const Vector4f& vec)
    : Tuple{vec}
    {}

    Vector(const Tuple& tup)
    : Tuple{tup}
    {}
};
