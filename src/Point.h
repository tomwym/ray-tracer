#pragma once

#include "Tuple.h"

class Point : public Tuple {
public:
    Point(const float& x, const float& y, const float& z)
    : Tuple{x,y,z,1.f}
    {}

    Point(const Vector4f& vec)
    : Tuple{vec}
    {}

    Point(const Tuple& tup)
    : Tuple{tup}
    {}
};
