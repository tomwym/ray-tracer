#pragma once

#include "Tuple.h"

class Point : public Tuple {
public:
    Point(const double& x, const double& y, const double& z);
    Point(const Vector4f& vec);
    Point(const Tuple& tup);
};
