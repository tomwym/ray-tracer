#pragma once

#include <tuple>
#include <cassert>

using uint = unsigned int;

class GridLinearizer {
    uint cols;
    uint rows;
    int index_from;
public:
    GridLinearizer(const uint rows, const uint cols, const int index_from = 0);
    auto Get(const uint rowi, const uint colj) const -> int;
    auto Get(const uint i) const -> std::tuple<int, int>;
};