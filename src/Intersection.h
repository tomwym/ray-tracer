#pragma once

#include "Geometry.h"

#include <memory>

class Point;
//class Ray;

class IntersectionComputation {
public:
    IntersectionComputation(
        const Intersection& intersection,
        const Ray& ray
    );
    std::unique_ptr<Intersection> intersection;
    std::unique_ptr<Point> point;
    std::unique_ptr<Vector> eyev;
    std::unique_ptr<Vector> normalv;
    std::unique_ptr<Point> over_point;
    bool inside;
};

class Intersection {
public:
    float t;
    std::unique_ptr<Geometry> geometry;

    Intersection(float t, std::unique_ptr<Geometry>&& geom);
    Intersection(const Intersection& copy);
    auto operator=(const Intersection& rhs) -> Intersection&;
    auto operator==(const Intersection& rhs) const -> bool;

    auto PrepareComputations(const Ray& ray) const -> IntersectionComputation;
};

using Intersections = std::vector<Intersection>;
auto Hit(const Intersections& intersections) -> Intersection;