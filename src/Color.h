#pragma once

#include "Vector_t.h"

class Color : public Vector4f {
public:
    float& red;
    float& green;
    float& blue;

    Color(const Vector4f& copy);
    Color(const Color& copy);
    Color(const float& red, const float& green, const float& blue);

    auto operator=(const Color& rhs) -> Color&;
    auto operator*(const float& scalar) const -> Color;
    auto operator*(const Color& rhs) const -> Color;

    auto String(const int& scale=1) const -> std::string;
};

// auto operator<<(std::ostream& os, const Color& color) -> std::ostream& {
//     os << color.String();
//     return os;
// }