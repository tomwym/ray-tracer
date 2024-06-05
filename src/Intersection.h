#pragma once

#include "Geometry.h"

#include <memory>

class Intersection {
public:
    std::unique_ptr<Geometry> geometry;
    float t;

    Intersection(float t, std::unique_ptr<Geometry>&& geom);
    Intersection(const Intersection& copy);
    auto operator==(const Intersection& rhs) const -> bool;
};

using Intersections = std::vector<Intersection>;
auto Hit(const Intersections& intersections) -> Intersection;