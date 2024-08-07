#pragma once

#include "Color.h"
#include "Constvals.h"

class Material_t {
public:
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;

    Material_t(
        const Color& color,
        const double& ambient,
        const double& diffuse,
        const double& specular,
        const double& shininess)
    : color{color}
    , ambient{ambient}
    , diffuse{diffuse}
    , specular{specular}
    , shininess{shininess}
    {}

    Material_t()
    : color{1,1,1}
    , ambient{0.1f}
    , diffuse{0.9f}
    , specular{0.9f}
    , shininess{200.f}
    {}

    auto operator==(const Material_t& rhs) const -> bool {
        return
            color == rhs.color &&
            EQF(ambient,rhs.ambient) &&
            EQF(diffuse,rhs.diffuse) &&
            EQF(specular,rhs.specular) &&
            EQF(shininess,rhs.shininess);
    }
};


class Light;
class Point;
class Vector;

auto Lighting(
    const Material_t& mat,
    const Light& light,
    const Point& pos,
    const Vector& eye,
    const Vector& norm,
    const bool in_shadow) -> Color;