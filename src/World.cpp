#include "World.h"

#include "Light.h"
#include "Geometry.h"
#include "Ray.h"
#include "Material.h"
#include "Transformations.h"
#include "Sphere.h"
#include "Intersection.h"

#include <algorithm>

World::World(std::unique_ptr<Light>&& light)
: light{std::move(light)}
{}

auto World::AddGeometry(std::unique_ptr<Geometry>&& geom) -> void {
    geometries.emplace_back(std::move(geom));
}

auto World::Intersect(const Ray& ray) const -> Intersections {
    Intersections buffer;
    for (const auto& geometry_ptr : geometries) {
        auto xs{geometry_ptr->Intersects(ray)};
        std::copy(xs.begin(), xs.end(), std::back_inserter(buffer));
    }
    std::sort(buffer.begin(),buffer.end(), [](const Intersection& a, const Intersection& b) { return a.t < b.t; });
    return buffer;
}

auto World::ColorAt(const Ray& ray) const -> Color {
    Intersections xs{Intersect(ray)};
    auto IntersectionPositive{[](const Intersection& x) -> bool { return x.t > EPSILON; }};
    auto it{std::find_if(xs.begin(), xs.end(), IntersectionPositive)};
    if (it == xs.end()) {
        return Color{0,0,0};
    }
    IntersectionComputation comp{it->PrepareComputations(ray)};
    return ShadeHit(comp);
}

auto World::ShadeHit(const IntersectionComputation& computation) const -> Color {
    return Lighting(
        computation.intersection->geometry->Material(),
        *light,
        *computation.point,
        *computation.eyev,
        *computation.normalv,
        PointShadowed(*computation.over_point)
    );
}

auto World::PointShadowed(const Point& point) const -> bool {
    Vector diff{light->position - point};
    float mag{diff.Magnitude()};

    Ray ray{point, diff.Normalize()};
    Intersections xs{Intersect(ray)};
    auto IntersectionPositiveAndLessThanMag{[mag](const Intersection& x) -> bool { return x.t > EPSILON && x.t < mag; }};
    auto it{std::find_if(xs.begin(), xs.end(), IntersectionPositiveAndLessThanMag)};
    return it != xs.end();
}



auto WorldFactory::DefaultWorld() -> World {
    World world{std::make_unique<Light>(Point{-10,10,-10},Color{1,1,1})};
    Material_t mat;
    mat.color = Color{0.8,1.0,0.6};
    mat.diffuse = 0.7f;
    mat.specular = 0.2f;
    Sphere s1;
    s1.Material(mat);
    Sphere s2;
    s2.Transform(Transformations::Scaling(0.5,0.5,0.5));
    world.AddGeometry(s1.Clone());
    world.AddGeometry(s2.Clone());
    return world;
}