#pragma once
#include "Tuple.h"

class Projectile {
public:
    Projectile(
        const float p_x, const float p_y, const float p_z,
        const float v_x, const float v_y, const float v_z)
    : position{Factory::Point(p_x, p_y, p_z)}
    , velocity{Factory::Point(v_x, v_y, v_z)}
    {}

    Projectile(const Tuple& pos, const Tuple& vel)
    : position{pos}
    , velocity{vel}
    {}

    auto operator=(const Projectile& other) -> Projectile& {
        position = other.position;
        velocity = other.velocity;
    }

    Tuple position;
    Tuple velocity;
};

class Environment;

auto Tick(const Environment& env, const Projectile& proj) -> Projectile;