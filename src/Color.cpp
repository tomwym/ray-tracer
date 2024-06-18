#include "Color.h"

#include <format>

Color::Color(const Vector4f& copy)
: Vector4f{copy}
, red{Vector4f::operator()(0)}
, green{Vector4f::operator()(1)}
, blue{Vector4f::operator()(2)}
{
}

Color::Color(const Color& copy)
: Vector4f{copy}
, red{Vector4f::operator()(0)}
, green{Vector4f::operator()(1)}
, blue{Vector4f::operator()(2)}
{
}

Color::Color(const double& red, const double& green, const double& blue)
: Vector4f{{red, green, blue, 0.0f}}
, red{Vector4f::operator()(0)}
, green{Vector4f::operator()(1)}
, blue{Vector4f::operator()(2)}
{
}

auto Color::operator=(const Color& rhs) -> Color& {
    Vector4f::operator=(rhs);

    red = Vector4f::operator()(0);
    green = Vector4f::operator()(1);
    blue = Vector4f::operator()(2);

    return *this;
}

auto Color::operator*(const double& scalar) const -> Color {
    return Vector4f::operator*(scalar);
}

auto Color::operator*(const Color& rhs) const -> Color {
    return Color{
        this->red   * rhs.red,
        this->green * rhs.green,
        this->blue  * rhs.blue
    };
}

auto Color::String(const int& scale) const -> std::string {
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
