#include "Constvals.h"

#include <cmath>

auto EQF(const float& a, const float& b) -> bool {
    return std::abs(a-b) < EPSILON;
}