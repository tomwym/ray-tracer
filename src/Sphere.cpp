#include "Sphere.h"

#include "Matrices.h"
#include "Ray.h"
#include "Intersection.h"
#include "Point.h"
#include "Vector.h"

auto Sphere::Clone() const -> GeometryPtr {
    return std::make_unique<Sphere>(*this);
}

auto Sphere::operator==(const Sphere& rhs) const -> bool {
    return true;
}
auto Sphere::Transform() const -> Matrix4f {
    return transform;
}

auto Sphere::Transform(const Matrix4f& other) -> void {
    transform = other;
}

auto Sphere::Intersects(const Ray& ray) const -> std::vector<Intersection> {
    Ray ray2{ray.Transform(Transform().Inverse())};
    Vector sphere_to_ray{ray2.origin - Point{0,0,0}};
    float a{ray2.direction.Dot(ray2.direction)};
    float b{2*ray2.direction.Dot(sphere_to_ray)};
    float c{sphere_to_ray.Dot(sphere_to_ray) - 1.f};
    float discriminant{b*b-4*a*c};

    if (discriminant < 0) {
        return {};
    }
    std::vector<Intersection> result;
    result.emplace_back(Intersection{(-b-std::sqrt(discriminant))/(2*a), std::make_unique<Sphere>(*this)});
    result.emplace_back(Intersection{(-b+std::sqrt(discriminant))/(2*a), std::make_unique<Sphere>(*this)});
    return result;
}

auto Sphere::Normal(const Point& world_point) const -> Vector {
    Point object_point{transform.Inverse()*world_point};
    Vector object_normal{object_point - Point{0,0,0}};
    Vector world_normal{transform.Inverse().Transpose()*object_normal};
    world_normal.w = 0;
    return world_normal.Normalize();
}

auto Sphere::Material() const -> Material_t {
    return material;
}

auto Sphere::Material(const Material_t& mat) -> void {
    material = mat;
}