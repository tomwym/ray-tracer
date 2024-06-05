#include "Projectile.h"
#include "Environment.h"
#include "Canvas.h"
#include "Tuple.h"

#include <iostream>
#include <fstream>

int main() {
    Canvas canvas{900, 550};
    Color red{1,0,0};

    Point position{0,1,0};
    Vector velocity{Vector{1.f,1.8f,0.f}.Normalize()*11.25};
    Projectile projectile{position,velocity};

    Tuple gravity{Vector(0.f,-0.1f,0.f)};
    Tuple wind{Vector(-0.01f,0.0f,0.f)};
    Environment env{gravity, wind};
    while (projectile.position.y > 0) {
        canvas.WritePixel(projectile.position.x, canvas.height-projectile.position.y, red);
        projectile = Tick(env, projectile);
    }

    std::ofstream file{"res/projectile.ppm", std::ios::trunc};
    file << canvas.ToPPM();
}