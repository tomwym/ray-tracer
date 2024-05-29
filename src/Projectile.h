#pragma once
#include "Point.h"
#include "Vector.h"

class Projectile {
public:
    Projectile(
        const float p_x, const float p_y, const float p_z,
        const float v_x, const float v_y, const float v_z)
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