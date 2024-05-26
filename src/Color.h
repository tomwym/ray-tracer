#pragma once

#include "Tuple.h"

#include <format>

class Color : public TupleF {
public:
    float& red;
    float& green;
    float& blue;

    Color(const TupleF& copy)
    : TupleF{copy}
    , red{TupleF::x}
    , green{TupleF::y}
    , blue{TupleF::z}
    {
    }

    Color(const Color& copy)
    : TupleF{copy}
    , red{TupleF::x}
    , green{TupleF::y}
    , blue{TupleF::z}
    {
    }

    auto operator=(const Color& rhs) -> Color& {
        TupleF::operator=(rhs);

        red = TupleF::x;
        green = TupleF::y;
        blue = TupleF::z;

        return *this;
    }

    Color(const float& red, const float& green, const float& blue)
    : TupleF{red, green, blue, 0.0f}
    , red{TupleF::x}
    , green{TupleF::y}
    , blue{TupleF::z}
    {
    }

    auto operator*(const float& scalar) const -> Color {
        return TupleF::operator*(scalar);
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