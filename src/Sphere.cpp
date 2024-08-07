#include "Sphere.h"

#include "Matrices.h"
#include "Ray.h"
#include "Intersection.h"
#include "Point.h"
#include "Vector.h"

Sphere::Sphere(const Sphere& other)
: Geometry{other.Transform(), other.Material()}
{}

Sphere::Sphere(const Matrix4d& transform, const Material_t& material)
: Geometry{transform, material}
{}

auto Sphere::operator==(const Sphere& rhs) const -> bool {
    return true;
}

auto Sphere::Clone() const -> GeometryPtr {
    return std::make_unique<Sphere>(*this);
}

auto Sphere::Intersects(const Ray& ray) const -> std::vector<Intersection> {
    Ray ray2{ray.Transform(Transform().Inverse())};
    Vector sphere_to_ray{ray2.origin - Point{0,0,0}};
    double a{ray2.direction.Dot(ray2.direction)};
    double b{2.f*ray2.direction.Dot(sphere_to_ray)};
    double c{sphere_to_ray.Dot(sphere_to_ray) - 1.f};
    double discriminant{b*b-4.f*a*c};

    if (discriminant < 0) {
        return {};
    }
    std::vector<Intersection> result;
    result.emplace_back(Intersection{(-b-std::sqrt(discriminant))/(2.f*a), std::make_unique<Sphere>(*this)});
    result.emplace_back(Intersection{(-b+std::sqrt(discriminant))/(2.f*a), std::make_unique<Sphere>(*this)});
    return result;
}

auto Sphere::Normal(const Point& world_point) const -> Vector {
    Point object_point{transform.Inverse()*world_point};
    Vector object_normal{object_point - Point{0,0,0}};
    Vector world_normal{transform.Inverse().Transpose()*object_normal};
    world_normal.w = 0;
    return world_normal.Normalize();
}

auto SphereFactory(const Matrix4d& transform, const Material_t& material) -> GeometryPtr {
    return std::make_unique<Sphere>(transform, material);
}
