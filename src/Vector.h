#pragma once

#include "Tuple.h"

class Vector : public Tuple {
public:
    Vector(const double& x, const double& y, const double& z);
    Vector(const Vector4f& vec);
    Vector(const Tuple& tup);
};
