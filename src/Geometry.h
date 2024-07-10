#pragma once

#include <memory>
#include <vector>

class Geometry;
using GeometryPtr = std::unique_ptr<Geometry>;

#include "Matrices.h"
#include "Material.h"

class GeometryPropertiesImpl {
protected:
    Matrix4d transform{Identity<double, 4>()};
    Material_t material;
public:
    GeometryPropertiesImpl() = default;
    GeometryPropertiesImpl(const Matrix4d& transform, const Material_t& mat);
    auto Transform() const -> Matrix4d;
    auto Transform(const Matrix4d& other) -> void;
    auto Material() const -> Material_t;
    auto Material() -> Material_t&;
    auto Material(const Material_t& other) -> void;
};

class Ray;
class Point;
class Vector;
class Intersection;

class Geometry : public GeometryPropertiesImpl {
public:
    Geometry() = default;
    Geometry(const Matrix4d& transform, const Material_t& mat)
    : GeometryPropertiesImpl{transform, mat}
    {}
    virtual auto Clone() const -> GeometryPtr = 0;
    virtual auto Intersects(const Ray& ray) const -> std::vector<Intersection> = 0;
    virtual auto Normal(const Point& world_point) const -> Vector = 0;
};
