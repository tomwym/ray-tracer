#pragma once

#include "Matrices.h"

class Transformations {
public:
    static auto Translation(const double& tx, const double& ty, const double& tz) -> Matrix4d;
    static auto Scaling(const double& sx, const double& sy, const double& sz) -> Matrix4d;
    static auto RotationX(const double& rad) -> Matrix4d;
    static auto RotationY(const double& rad) -> Matrix4d;
    static auto RotationZ(const double& rad) -> Matrix4d;
    static auto Shearing(const double& xy, const double& xz,
                         const double& yx, const double& yz,
                         const double& zx, const double& zy) -> Matrix4d;

};

class Point;
class Vector;
auto ViewTransform(const Point& from, const Point& to, const Vector& up) -> Matrix4d;
