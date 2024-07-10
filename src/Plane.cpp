#include "Plane.h"
#include "Vector.h"
#include "Ray.h"

Plane::Plane(const Matrix4d& transform, const Material_t& material)
: Geometry{transform, material}
{}

auto Plane::Clone() const -> GeometryPtr {
    return std::make_unique<Plane>(*this);
}

auto Plane::Intersects(const Ray& ray) const -> std::vector<Intersection> {
    // Parallel and coplanar test
    if (ray.direction.y == 0) {
        return {};
    }
    const double t{-ray.origin.y / ray.direction.y};
    return {{t, Clone()}};
}

auto Plane::Normal(const Point& world_point) const -> Vector {
    return Vector{0,1,0};
}
