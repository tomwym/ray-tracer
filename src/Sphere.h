#pragma once

#include "Geometry.h"
#include "Matrices.h"
#include "Material.h"

#include <memory>

class Sphere;
class Ray;
class Point;

class Sphere : public Geometry {
    Matrix4f transform{Identity<float, 4>()};
    Material_t material{};
public:
    auto Clone() const -> GeometryPtr override;
    auto operator==(const Sphere& rhs) const -> bool;
    auto Transform() const -> Matrix4f;
    auto Transform(const Matrix4f& other) -> void;
    auto Intersects(const Ray& ray) const -> std::vector<Intersection> override;
    auto Normal(const Point& world_point) const -> Vector override;
    auto Material() const -> Material_t override;
    auto Material(const Material_t& mat) -> void;
};
