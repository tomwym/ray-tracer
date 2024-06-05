#pragma once

#include "Color.h"
#include "Point.h"

class Light {
public:
    Light(const Point& position, const Color& intensity)
    : position{position}
    , intensity{intensity}
    {}

    Point position;
    Color intensity;
};
