#pragma once

#include <tuple>
#include <cassert>

using uint = unsigned int;

class GridLinearizer {
    uint cols;
    uint rows;
    int index_from;
public:
    GridLinearizer(const uint rows, const uint cols, const int index_from = 0)
    : rows{rows}
    , cols{cols}
    , index_from{index_from}
    {}

    auto Get(const uint rowi, const uint colj) -> int {
        if (rowi-index_from >= rows || colj-index_from >= cols) {
            assert(((void)"invalid_index", false));
            return -1;
        }
        return (rowi-index_from)*cols + (colj-index_from);
    }

    auto Get(const uint i) -> std::tuple<int, int> {
        if (i >= rows*cols) {
            assert(((void)"invalid_index", false));
            return {-1,-1};
        }
        const int rowi{(int)(i/cols+index_from)};
        const int colj{(int)(i%cols+index_from)};
        return {rowi, colj};
    }
};