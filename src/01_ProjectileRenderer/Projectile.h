#pragma once
#include "Point.h"
#include "Vector.h"

class Projectile {
public:
    Projectile(
        const double p_x, const double p_y, const double p_z,
        const double v_x, const double v_y, const double v_z)
    : position{p_x, p_y, p_z}
    , velocity{v_x, v_y, v_z}
    {}

    Projectile(const Point& pos, const Vector& vel)
    : position{pos}
    , velocity{vel}
    {}

    Point position;
    Vector velocity;
};

class Environment;

auto Tick(const Environment& env, const Projectile& proj) -> Projectile;