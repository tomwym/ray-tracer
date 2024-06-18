#include "Ray.h"

Ray::Ray(const Point& origin, const Vector& direction)
: origin{origin}
, direction{direction}
{}

auto Ray::Position(const double& t) const -> Point {
    return origin + direction*t;
}

auto Ray::Intersects(const Geometry& s) const -> std::vector<Intersection> {
    return s.Intersects(*this);
}

auto Ray::Transform(const Matrix4d& matrix) const -> Ray {
    return Ray{
        matrix*origin,
        matrix*direction
    };
}
