#pragma once

#include "Geometry.h"
#include "Matrices.h"
#include "Material.h"

#include <memory>

class Sphere;
class Ray;
class Point;

class Sphere : public Geometry {
public:
    Sphere() = default;
    Sphere(const Sphere&);
    Sphere(const Matrix4d& transform, const Material_t& material);
    auto operator==(const Sphere& rhs) const -> bool;
    auto Clone() const -> GeometryPtr override;
    auto Intersects(const Ray& ray) const -> std::vector<Intersection> override;
    auto Normal(const Point& world_point) const -> Vector override;
};

auto SphereFactory(const Matrix4d& transform, const Material_t& material) -> GeometryPtr;
