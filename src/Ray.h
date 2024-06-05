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
    auto Position(const float& t) const -> Point;
    auto Intersects(const Geometry& s) const -> std::vector<Intersection>;
    auto Transform(const Matrix4f& matrix) const -> Ray;
};