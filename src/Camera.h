#pragma once

#include "Matrices.h"

class Ray;
class World;
class Canvas;
struct Initializers;

class Camera {
public:
    using PixelCount = unsigned int;
    using Radians = float;

    const PixelCount hsize;
    const PixelCount vsize;
    const Radians fov;
    const Matrix4f transform;
    const float pixel_dimension;
    float half_width;
    float half_height;

    Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov);
    Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov, const Matrix4f& transform);

    auto RayThroughPixel(const uint& px, const uint& py) const -> Ray;
    auto Render(const World& world) const -> Canvas;

private:
    Camera(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov, const Matrix4f& transform, const Initializers& values);

    auto GetInitializers(const PixelCount& hsize, const PixelCount& vsize, const Radians& fov) const -> Initializers;
};