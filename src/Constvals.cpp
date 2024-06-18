#include "Constvals.h"

#include <cmath>

auto EQF(const double& a, const double& b) -> bool {
    return std::abs(a-b) < EPSILON;
}