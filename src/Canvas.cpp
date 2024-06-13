#include "Canvas.h"

#include <sstream>
#include <format>

Canvas::Canvas(const unsigned int width, const unsigned int height, const Color& color)
: width{width}
, height{height}
, idx_cnvrt{std::make_unique<GridLinearizer>(height, width)}
, pixels{std::vector<Color>(width*height, color)}
{}

auto Canvas::WritePixel(const unsigned int x, const unsigned int y, const Color& color) -> void {
    pixels[idx_cnvrt->Get(y, x)] = color;
}

auto Canvas::PixelAt(const unsigned int x, const unsigned int y) const -> Color {
    return pixels[idx_cnvrt->Get(y, x)];
}

auto Canvas::ToPPM() const -> PPM_t {
    return PPMHeader() + PPMBody();
}

auto Canvas::PPMHeader() const -> PPM_t {
    std::stringstream ss;
    ss << "P3\n";
    ss << std::format("{} {}\n", std::to_string(width), std::to_string(height));
    ss << "255\n";
    return ss.str();
}

auto Canvas::PPMBody() const -> PPM_t {
    std::string buffer;
    std::stringstream ss;
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            // The next color string to be added
            std::string color_string{pixels[idx_cnvrt->Get(y, x)].String(255)};
            // If the color string plus leading whitespace exceeds 70, flush the stream.
            if (ss.str().size() + color_string.size() + 1 > 70) {
                ss << '\n';
                buffer += ss.str();
                ss.str(std::string{});
            }
            // If the stream is empty, ignore leading whitespace.
            if (ss.str().size() == 0) {
                ss << color_string;
            }
            // Otherwise...
            else {
                ss << ' ' << color_string;
            }
        }
        ss << '\n';
        buffer += ss.str();
        ss.str(std::string{});
    }
    return buffer;
}