#include "Projectile.h"
#include "Environment.h"

auto Tick(const Environment& env, const Projectile& proj) -> Projectile {
    Tuple position{proj.position + proj.velocity};
    Tuple velocity{proj.velocity + env.gravity + env.wind};
    return Projectile{position, velocity};
}