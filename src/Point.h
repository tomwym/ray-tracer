#pragma once

#include "Tuple.h"

class Point : public Tuple {
public:
    Point(const float& x, const float& y, const float& z);
    Point(const Vector4f& vec);
    Point(const Tuple& tup);
};
