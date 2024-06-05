#include "Ray.h"

Ray::Ray(const Point& origin, const Vector& direction)
: origin{origin}
, direction{direction}
{}

auto Ray::Position(const float& t) const -> Point {
    return origin + direction*t;
}

auto Ray::Intersects(const Geometry& s) const -> std::vector<Intersection> {
    return s.Intersects(*this);
}

auto Ray::Transform(const Matrix4f& matrix) const -> Ray {
    return Ray{
        matrix*origin,
        matrix*direction
    };
}
