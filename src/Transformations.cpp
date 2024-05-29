#include "Transformations.h"

#include <cmath>

using std::cos;
using std::sin;

auto Transformations::Translation(const float& tx, const float& ty, const float& tz) -> Matrix4f {
    Matrix4f buffer{Identity<float, 4>()};
    buffer(0,3) = tx;
    buffer(1,3) = ty;
    buffer(2,3) = tz;
    return buffer;
}

auto Transformations::Scaling(const float &sx, const float &sy, const float &sz) -> Matrix4f {
    Matrix4f buffer{Identity<float, 4>()};
    buffer(0,0) = sx;
    buffer(1,1) = sy;
    buffer(2,2) = sz;
    return buffer;
}

auto Transformations::RotationX(const float& rad) -> Matrix4f {
    Matrix4f buffer{Identity<float, 4>()};
    buffer(1,1) = std::cos(rad);
    buffer(1,2) = -std::sin(rad);
    buffer(2,1) = std::sin(rad);
    buffer(2,2) = std::cos(rad);

    return buffer;
}
auto Transformations::RotationY(const float& rad) -> Matrix4f {
    Matrix4f buffer{Identity<float, 4>()};
    buffer(0,0) = std::cos(rad);
    buffer(0,2) = std::sin(rad);
    buffer(2,0) = -std::sin(rad);
    buffer(2,2) = std::cos(rad);

    return buffer;
}
auto Transformations::RotationZ(const float& rad) -> Matrix4f {
    Matrix4f buffer{Identity<float, 4>()};
    buffer(0,0) = std::cos(rad);
    buffer(0,1) = -std::sin(rad);
    buffer(1,0) = std::sin(rad);
    buffer(1,1) = std::cos(rad);

    return buffer;
}

auto Transformations::Shearing(const float& xy, const float& xz,
                               const float& yx, const float& yz,
                               const float& zx, const float& zy) -> Matrix4f {
    Matrix4f buffer{Identity<float, 4>()};
    buffer(0,1) = xy;
    buffer(0,2) = xz;
    buffer(1,0) = yx;
    buffer(1,2) = yz;
    buffer(2,0) = zx;
    buffer(2,1) = zy;
    return buffer;
}