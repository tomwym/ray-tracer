#include "Point.h"

Point::Point(const float& x, const float& y, const float& z)
: Tuple{x,y,z,1.f}
{}

Point::Point(const Vector4f& vec)
: Tuple{vec}
{}

Point::Point(const Tuple& tup)
: Tuple{tup}
{}