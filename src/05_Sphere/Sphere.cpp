#include "Canvas.h"
#include "Point.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Transformations.h"

#include <tuple>
#include <fstream>
using uint = unsigned int;

template<typename T>
struct P {
    P(const T x, const T y)
    : x{x}
    , y{y}
    {}
    T x;
    T y;
};
using Pi = P<int>;
using Pui = P<uint>;
using Pf = P<double>;

class XYMapper {
public:
    Point origin;
    Pi max;
    Pi min;
    int z;
    Pui pixels;
    Pf dpixel;
public:

    XYMapper(const Point& origin,
        const int max_x, const int max_y,
        const int min_x, const int min_y,
        const int z,
        const uint pixel_x, const uint pixel_y)
    : origin{origin}
    , max{max_x, max_y}
    , min{min_x, min_y}
    , z{z}
    , pixels{pixel_x, pixel_y}
    , dpixel{(max_x - min_x)/((double)pixel_x),
             (max_y - min_y)/((double)pixel_y)}
    {}

    auto GetRayAtPixel(const uint i, const uint j) const -> Ray {
        auto[x, y]{MapPixelToXY(i, j)};
        return Ray{origin, (Point(x, y, z) - origin).Normalize()};
    }

    auto MapPixelToXY(const uint i, const uint j) const -> std::tuple<double, double> {
        return {
            min.x + dpixel.x*0.5 + j*dpixel.x,
            max.y - dpixel.y*0.5 - i*dpixel.y
        };
    }
};

int main() {
    uint dimx{200};
    uint dimy{200};
    Point origin{1,1,-5};
    XYMapper mapper(
        origin,
        5,5,
        -5,-5,
        5,
        dimx, dimy);
    Canvas canvas{dimx,dimy};

    Material_t mat;
    mat.color = Color{1,0.2,1};
    Matrix4d transform {Transformations::Scaling(2,1,1)};
    Sphere s;
    s.Material(mat);
    s.Transform(transform);

    Point light_pos{-10,20,0};
    Color light_color{1,1,1};
    Light light{light_pos,light_color};

    for (int i=0; i<dimy; ++i) {
        for (int j=0; j<dimx; ++j) {
            Ray ray{mapper.GetRayAtPixel(i, j)};
            auto xs{ray.Intersects(s)};
            if (xs.size()) {
                Intersection first_hit{xs[0]};
                Point surface_point{ray.Position(first_hit.t)};
                Vector norm{first_hit.geometry->Normal(surface_point)};
                Vector eye{-ray.direction};
                Color color{Lighting(first_hit.geometry->Material(),light,surface_point,eye,norm,false)};
                canvas.WritePixel(j, i, color);
            }
        }
    }
    std::ofstream file{"res/sphere.ppm", std::ios::trunc};
    file << canvas.ToPPM();
}