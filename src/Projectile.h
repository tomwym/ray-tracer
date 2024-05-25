#pragma once
#include "Tuple.h"

class Projectile {
public:
    Projectile(
        const float p_x, const float p_y, const float p_z,
        const float v_x, const float v_y, const float v_z)
    : position{PointF(p_x, p_y, p_z)}
    , velocity{PointF(v_x, v_y, v_z)}
    {}

    Projectile(const TupleF& pos, const TupleF& vel)
    : position{pos}
    , velocity{vel}
    {}

    TupleF position;
    TupleF velocity;
};

class Environment;

auto Tick(const Environment& env, const Projectile& proj) -> Projectile;