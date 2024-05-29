#include "Canvas.h"
#include "Point.h"
#include "Vector.h"
#include "Transformations.h"

#include <numbers>
#include <fstream>

int main() {
    int dim{120};
    Canvas canvas{dim,dim};
    Color white{1,1,1};
    float radius{dim*0.4};
    Point point{radius,0,0};
    float angle{0.f};
    for (int i=0; i<12; ++i) {
        Point transformed_point{Transformations::Translation(dim/2,dim/2,0)*Transformations::RotationZ(angle)*point};
        canvas.WritePixel(transformed_point.x, transformed_point.y, white);
        angle += std::numbers::pi/6;
    }
    std::ofstream file{"res/clock.ppm", std::ios::trunc};
    file << canvas.ToPPM();
}