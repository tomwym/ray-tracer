#pragma once

#include "Matrices.h"

class Transformations {
public:
    static auto Translation(const float& tx, const float& ty, const float& tz) -> Matrix4f;
    static auto Scaling(const float& sx, const float& sy, const float& sz) -> Matrix4f;
    static auto RotationX(const float& rad) -> Matrix4f;
    static auto RotationY(const float& rad) -> Matrix4f;
    static auto RotationZ(const float& rad) -> Matrix4f;
    static auto Shearing(const float& xy, const float& xz,
                         const float& yx, const float& yz,
                         const float& zx, const float& zy) -> Matrix4f;

};