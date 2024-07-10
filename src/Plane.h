#pragma once
#include "Geometry.h"



class Plane : public Geometry {
public:
    Plane() = default;
    Plane(const Matrix4d& transform, const Material_t& material);
    auto Clone() const -> GeometryPtr override;
    auto Intersects(const Ray& ray) const -> std::vector<Intersection> override;
    auto Normal(const Point& world_point) const -> Vector override;
};