#include "Intersection.h"
#include "Ray.h"

#include "Constvals.h"

#include <vector>
#include <limits>
#include <ranges>
#include <cassert>

IntersectionComputation::IntersectionComputation(
    const Intersection& intersection,
    const Ray& ray
)
: intersection{std::make_unique<Intersection>(intersection)}
, point{std::make_unique<Point>(ray.Position(intersection.t))}
, eyev{std::make_unique<Vector>(-ray.direction)}
, normalv{std::make_unique<Vector>(intersection.geometry->Normal(*point))}
, over_point{std::make_unique<Point>(*point + normalv->Normalize()*(EPSILON))}
, inside{false}
{
    if (normalv->Dot(*eyev) < 0.f) {
        inside = true;
        normalv = std::make_unique<Vector>(-*normalv);
        over_point = std::make_unique<Point>(*point + normalv->Normalize()*(EPSILON));
    }
}

Intersection::Intersection(float t, std::unique_ptr<Geometry>&& geom)
: t{t}
, geometry{std::move(geom)}
{}

Intersection::Intersection(const Intersection& copy)
: t{copy.t}
, geometry{copy.geometry->Clone()}
{}

auto Intersection::operator=(const Intersection& rhs) -> Intersection& {
    t = rhs.t;
    geometry = rhs.geometry->Clone();
    return *this;
}

auto Intersection::operator==(const Intersection& rhs) const -> bool {
    return EQF(t, rhs.t);
    // geomtry->Interface() == rhs.geometry->Interface() &&
}

auto Intersection::PrepareComputations(const Ray& ray) const -> IntersectionComputation {
    return IntersectionComputation(*this, ray);
}

auto Hit(const Intersections& intersections) -> Intersection {
    int min{std::numeric_limits<int>::max()};
    int min_idx{-1};
    for (const auto& [i, ix] : intersections | std::ranges::views::enumerate) {
        if (ix.t > 0 && ix.t < min) {
            min = ix.t;
            min_idx = i;
        }
    }
    assert(min_idx >= 0);
    return intersections[min_idx];
}
