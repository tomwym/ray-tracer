#pragma once

#include <memory>
#include <vector>

class Geometry;
using GeometryPtr = std::unique_ptr<Geometry>;

class Ray;
class Point;
class Vector;
class Intersection;
class Material_t;

class Geometry {
public:
    virtual auto Clone() const -> GeometryPtr = 0;
    virtual auto Intersects(const Ray& ray) const -> std::vector<Intersection> = 0;
    virtual auto Normal(const Point& world_point) const -> Vector = 0;
    virtual auto Material() const -> Material_t = 0;
};
