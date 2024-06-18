#pragma once

#include "Matrices.h"

class Ray;
class World;
class Canvas;
struct Initializers;

class Camera {
public:
    using PixelCount = unsigned int;
    using Radians = double;

    const PixelCount hsize;
    const PixelCount vsize;
    const Radians fov;
    const Matrix4d transform;
    const double pixel_dimension;
    double half_width;
    double half_height;

    Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov);
    Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov, const Matrix4d& transform);

    auto RayThroughPixel(const uint& px, const uint& py) const -> Ray;
    auto Render(const World& world) const -> Canvas;

private:
    Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov, const Matrix4d& transform, const Initializers& values);

    auto GetInitializers(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov) const -> Initializers;
};