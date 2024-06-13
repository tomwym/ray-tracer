#pragma once

#include <vector>
#include <memory>

class Geometry;
class Light;
class Ray;
class Intersection;
class IntersectionComputation;
class Color;
using Intersections = std::vector<Intersection>;

class World {
public:
    World(std::unique_ptr<Light>&& light);
    auto AddGeometry(std::unique_ptr<Geometry>&& geom) -> void;
    auto Intersect(const Ray& ray) const -> Intersections;
    auto ShadeHit(const IntersectionComputation&) const -> Color;
    auto ColorAt(const Ray& ray) const -> Color;

    std::unique_ptr<Light> light;
    std::vector<std::unique_ptr<Geometry>> geometries;
};

class WorldFactory {
public:
    static auto DefaultWorld() -> World;
};
