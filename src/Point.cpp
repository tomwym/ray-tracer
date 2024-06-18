#include "Point.h"

Point::Point(const double& x, const double& y, const double& z)
: Tuple{x,y,z,1.f}
{}

Point::Point(const Vector4f& vec)
: Tuple{vec}
{}

Point::Point(const Tuple& tup)
: Tuple{tup}
{}