#pragma once

#include "Color.h"
#include "GridLinearizer.h"

#include <memory>
#include <vector>
#include <string>

using PPM_t = std::string;

class Canvas {
    std::unique_ptr<GridLinearizer> idx_cnvrt;
    std::vector<Color> pixels;

public:
    unsigned int width;
    unsigned int height;
    unsigned int max_ppm{255};

    Canvas(const unsigned int width, const unsigned int height, const Color& color = Color{0,0,0});

    auto WritePixel(const unsigned int x, const unsigned int y, const Color& color) -> void;
    auto PixelAt(const unsigned int x, const unsigned int y) const -> Color;

    auto ToPPM() const -> PPM_t;
    auto PPMHeader() const -> PPM_t;
    auto PPMBody() const -> PPM_t;
private:

};