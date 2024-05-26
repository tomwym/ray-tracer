#include "Projectile.h"
#include "Environment.h"
#include "Canvas.h"

#include <iostream>
#include <fstream>

int main() {
    Canvas canvas{900, 550};
    Color red{1,0,0};

    TupleF position{PointF(0,1,0)};
    TupleF velocity{VectorF(1,1.8,0).Normalize()*11.25};
    Projectile projectile{position,velocity};

    TupleF gravity{VectorF(0,-0.1,0)};
    TupleF wind{VectorF(-0.01,0,0)};
    Environment env{gravity, wind};
    while (projectile.position.y > 0) {
        canvas.WritePixel(projectile.position.x, canvas.height-projectile.position.y, red);
        projectile = Tick(env, projectile);
    }

    std::ofstream file{"res/projectile.ppm", std::ios::trunc};
    file << canvas.ToPPM();
}