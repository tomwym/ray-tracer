#include "GridLinearizer.h"

GridLinearizer::GridLinearizer(const uint rows, const uint cols, const int index_from)
: rows{rows}
, cols{cols}
, index_from{index_from}
{}

auto GridLinearizer::Get(const uint rowi, const uint colj) const -> int {
    if (rowi-index_from >= rows || colj-index_from >= cols) {
        assert(((void)"invalid_index", false));
        return -1;
    }
    return (rowi-index_from)*cols + (colj-index_from);
}

auto GridLinearizer::Get(const uint i) const -> std::tuple<int, int> {
    if (i >= rows*cols) {
        assert(((void)"invalid_index", false));
        return {-1,-1};
    }
    const int rowi{(int)(i/cols+index_from)};
    const int colj{(int)(i%cols+index_from)};
    return {rowi, colj};
}