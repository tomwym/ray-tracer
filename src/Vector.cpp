#include "Vector.h"

Vector::Vector(const double& x, const double& y, const double& z)
: Tuple{x,y,z,0.f}
{}

Vector::Vector(const Vector4f& vec)
: Tuple{vec}
{}

Vector::Vector(const Tuple& tup)
: Tuple{tup}
{}