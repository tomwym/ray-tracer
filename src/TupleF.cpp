#include "Tuple.h"

template class Tuple<float>;
using TupleF = Tuple<float>;

template auto operator*<float>(const float& scalar, const TupleF& tup) -> TupleF;
template auto Magnitude<float>(const TupleF& tup) -> float;
template auto Normalize<float>(const TupleF& tup) -> TupleF;
template auto Dot(const TupleF& lhs, const TupleF& rhs) -> float;
template auto Cross(const TupleF& lhs, const TupleF& rhs) -> TupleF;

template auto Point<float>(const float& x, const float& y, const float& z) -> TupleF;
template auto Vector<float>(const float& x, const float& y, const float& z) -> TupleF;

auto PointF(const float& x, const float& y, const float& z) -> TupleF {
    return Point<float>(x, y, z);
}

auto VectorF(const float& x, const float& y, const float& z) -> TupleF {
    return Vector<float>(x, y, z);
}