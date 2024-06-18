#pragma once

#include "Point.h"
#include "Vector.h"
#include "Intersection.h"
#include "Matrices.h"

#include <vector>

class Ray {
public:
    Point origin;
    Vector direction;

    Ray(const Point& origin, const Vector& direction);
    auto Position(const double& t) const -> Point;
    auto Intersects(const Geometry& s) const -> std::vector<Intersection>;
    auto Transform(const Matrix4d& matrix) const -> Ray;
};