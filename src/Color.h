#pragma once

#include "Vector_t.h"

#include <format>

class Color : public Vector4f {
public:
    float& red;
    float& green;
    float& blue;

    Color(const Vector4f& copy)
    : Vector4f{copy}
    , red{Vector4f::operator()(0)}
    , green{Vector4f::operator()(1)}
    , blue{Vector4f::operator()(2)}
    {
    }

    Color(const Color& copy)
    : Vector4f{copy}
    , red{Vector4f::operator()(0)}
    , green{Vector4f::operator()(1)}
    , blue{Vector4f::operator()(2)}
    {
    }

    auto operator=(const Color& rhs) -> Color& {
        Vector4f::operator=(rhs);

        red = Vector4f::operator()(0);
        green = Vector4f::operator()(1);
        blue = Vector4f::operator()(2);

        return *this;
    }

    Color(const float& red, const float& green, const float& blue)
    : Vector4f{{red, green, blue, 0.0f}}
    , red{Vector4f::operator()(0)}
    , green{Vector4f::operator()(1)}
    , blue{Vector4f::operator()(2)}
    {
    }

    auto operator*(const float& scalar) const -> Color {
        return Vector4f::operator*(scalar);
    }

    auto operator*(const Color& rhs) -> Color {
        return Color{
            this->red   * rhs.red,
            this->green * rhs.green,
            this->blue  * rhs.blue
        };
    }

    auto String(const int& scale=1) const -> std::string {
        using std::to_string;
        auto Clamp = [&scale](const int val) -> int {
            if (val > scale) {
                return scale;
            }
            if (val < 0) {
                return 0;
            }
            return val;
        };
        return std::format("{} {} {}",
            to_string(Clamp((int)std::round(red*scale))),
            to_string(Clamp((int)std::round(green*scale))),
            to_string(Clamp((int)std::round(blue*scale))));
    }

};

// auto operator<<(std::ostream& os, const Color& color) -> std::ostream& {
//     os << color.String();
//     return os;
// }