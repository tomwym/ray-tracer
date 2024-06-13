#include "Transformations.h"
#include "Point.h"
#include "Vector.h"

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

auto ViewTransform(const Point& from, const Point& to, const Vector& up) -> Matrix4f {
    Vector forward{(to - from).Normalize()};
    Vector left{forward.Cross(up.Normalize())};
    Vector true_up{left.Cross(forward)};
    Matrix4f orientation{{
        left.x,left.y,left.z,0.f,
        true_up.x,true_up.y,true_up.z,0.f,
        -forward.x,-forward.y,-forward.z,0.f,
        0.f,0.f,0.f,1.f
    }};
    return orientation * Transformations::Translation(-from.x,-from.y,-from.z);
}