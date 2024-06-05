#include "Intersection.h"

#include "Constvals.h"

#include <vector>
#include <limits>
#include <ranges>
#include <cassert>

Intersection::Intersection(float t, std::unique_ptr<Geometry>&& geom)
: t{t}
, geometry{std::move(geom)}
{}

Intersection::Intersection(const Intersection& copy)
: t{copy.t}
, geometry{copy.geometry->Clone()}
{}

auto Intersection::operator==(const Intersection& rhs) const -> bool {
    return EQF(t, rhs.t);
    // geomtry->Interface() == rhs.geometry->Interface() &&
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