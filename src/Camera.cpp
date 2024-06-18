#include "Camera.h"
#include "Ray.h"
#include "World.h"
#include "Canvas.h"

#include <cmath>

struct Initializers {
    double pixel_dimension;
    double half_width;
    double half_height;
};

Camera::Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov)
: Camera{hsize,vsize,fov,Identity<double,4>(),GetInitializers(hsize,vsize,fov)}
{}

Camera::Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov, const Matrix4d& transform)
: Camera{hsize,vsize,fov,transform,GetInitializers(hsize,vsize,fov)}
{}

Camera::Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov, const Matrix4d& transform, const Initializers& values)
: hsize{hsize}
, vsize{vsize}
, fov{fov}
, transform{transform}
, pixel_dimension{values.pixel_dimension}
, half_width{values.half_width}
, half_height{values.half_height}
{}

auto Camera::GetInitializers(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov) const -> Initializers {
    Radians half_view{std::tan(fov/2)};
    double aspect{(double)hsize/(double)vsize};

    double half_width;
    double half_height;
    if (aspect >= 1) { // landscape
        half_width = half_view;
        half_height = half_view / aspect;
    }
    else { // portrait
        half_width = half_view * aspect;
        half_height = half_view;
    }
    return {half_width * 2 / hsize, half_width, half_height};
}

auto Camera::RayThroughPixel(const uint& px, const uint& py) const -> Ray {
    double xoffset{(px + 0.5f) * pixel_dimension};
    double yoffset{(py + 0.5f) * pixel_dimension};

    double world_x{half_width - xoffset};
    double world_y{half_height - yoffset};

    Point pixel{transform.Inverse() * Point{world_x, world_y, -1}};
    Point origin{transform.Inverse() * Point{0,0,0}};
    Vector direction{(pixel - origin).Normalize()};

    return Ray{origin, direction};
}

auto Camera::Render(const World& world) const -> Canvas {
    Canvas image{hsize, vsize};
    for (int i=0; i<vsize; ++i) {
        for (int j=0; j<hsize; ++j) {
            Ray ray{RayThroughPixel(j,i)};
            Color c{world.ColorAt(ray)};
            image.WritePixel(j, i, c);
        }
    }
    return image;
}
