#pragma once

#include "Tuple.h"

class Vector : public Tuple {
public:
    Vector(const float& x, const float& y, const float& z);
    Vector(const Vector4f& vec);
    Vector(const Tuple& tup);
};
