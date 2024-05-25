#include "Projectile.h"
#include "Environment.h"

auto Tick(const Environment& env, const Projectile& proj) -> Projectile {
    TupleF position{proj.position + proj.velocity};
    TupleF velocity{proj.velocity + env.gravity + env.wind};
    return Projectile{position, velocity};
}