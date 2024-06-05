#pragma once

#include <array>
#include <ranges>
#include <type_traits>
#include <iterator>
#include <memory>
#include <map>

#include "Constvals.h"
#include "GridLinearizer.h"
#include "Vector_t.h"

using uint = unsigned int;

template<typename T, std::size_t N>
class Matrix {
    std::array<T, N*N> arr;
    std::unique_ptr<GridLinearizer> idx_cnvrt{std::make_unique<GridLinearizer>(N, N)};
public:
    Matrix()
    : arr{}
    {}
    Matrix(std::array<T, N*N> list)
    : arr{list}
    {}

    Matrix(const Matrix<T,N>& copy) {
        arr = copy.arr;
        idx_cnvrt = std::make_unique<GridLinearizer>(*copy.idx_cnvrt);

    }

    auto operator=(const Matrix<T,N>& rhs) -> Matrix<T,N>& {
        arr = rhs.arr;
        idx_cnvrt = std::make_unique<GridLinearizer>(*rhs.idx_cnvrt);
        return *this;
    }

    auto operator()(const uint& ij) -> T& {
        return arr[ij];
    }

    auto operator()(const uint& ij) const -> const T& {
        return arr[ij];
    }

    auto operator()(const uint& i, const uint j) -> T& {
        return arr[idx_cnvrt->Get(i,j)];
    }

    auto operator()(const uint& i, const uint j) const -> const T& {
        return arr[idx_cnvrt->Get(i,j)];
    }

    auto begin() -> std::array<T, N*N>::iterator { return arr.begin(); }
    auto end() -> std::array<T, N*N>::iterator { return arr.end(); }
    auto begin() const -> std::array<T, N*N>::const_iterator { return arr.begin(); }
    auto end() const -> std::array<T, N*N>::const_iterator { return arr.end(); }

    auto operator==(const Matrix<T,N>& mat) const -> bool {
        for (const auto& [i, val] : arr | std::ranges::views::enumerate) {
            if (std::abs(val-mat.arr[i]) >= EPSILON) {
                return false;
            }
        }
        return true;
    }

    auto operator!=(const Matrix<T,N>& mat) const -> bool {
        return !this->operator==(mat);
    }

    auto Row(const unsigned int i) const -> Vector_t<T, N> {
        std::array<T, N> buffer;
        for (int j=0; j<N; ++j) {
            buffer[j] = arr[idx_cnvrt->Get(i,j)];
        }
        return Vector_t<T, N>{buffer};
    }

    auto Col(const unsigned int j) const -> Vector_t<T, N> {
        std::array<T, N> buffer;
        for (int i=0; i<N; ++i) {
            buffer[i] = arr[idx_cnvrt->Get(i,j)];
        }
        return Vector_t<T, N>{buffer};
    }

    auto operator*(const T& rhs) const -> Matrix<T, N> {
        Matrix<T, N> buffer;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                buffer(i, j) = rhs * this->operator()(i,j);
            }
        }
        return buffer;
    }

    auto operator*(const Matrix<T, N>& rhs) const -> Matrix<T, N> {
        Matrix<T, N> buffer;
        std::map<uint, Vector_t<T, N>> col_map;
        for (int j=0; j<N; ++j) {
            col_map[j] = rhs.Col(j);
        }
        for (int i=0; i<N; ++i) {
            Vector_t<T, N> rowi{this->Row(i)};
            for (int j=0; j<N; ++j) {
                buffer(i, j) = rowi.Dot(col_map[j]);
            }
        }
        return buffer;
    }

    auto operator*(const Vector_t<T, N>& rhs) const -> Vector_t<T, N> {
        Vector_t<T, N> buffer;
        for (int i=0; i<N; ++i) {
            buffer(i) = this->Row(i).Dot(rhs);
        }
        return buffer;
    }

    auto Transpose() const -> Matrix<T, N> {
        Matrix<T, N> buffer;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                buffer(i,j) = this->operator()(j,i);
            }
        }
        return buffer;
    }

    template<std::size_t M = N>
    auto Determinant() const -> typename std::enable_if_t<(M == 2), T> {
        return arr[0]*arr[3] - arr[1]*arr[2];
    }

    template<std::size_t M = N>
    auto Determinant() const -> typename std::enable_if_t<(M > 2), T> {
        // perform over a column
        T det{0};
        Vector_t<T, N> row{this->Row(0)};
        for (int j=0; j<N; ++j) {
            det += row(j)*Cofactor(0,j);
        }
        return det;
    }

    auto SubMatrix(const uint& removed_row, const uint& removed_col) const -> Matrix<T,N-1> {
        typename std::array<T,(N-1)*(N-1)> buffer;
        typename std::array<T,(N-1)*(N-1)>::iterator buffer_it{buffer.begin()};
        typename std::array<T,N*N>::const_iterator this_it{this->begin()};

        for (int i=0; i<N; ++i) {
            if (i == removed_row) {
                std::advance(this_it, N);
                continue;
            }
            for (int j=0; j<N; ++j) {
                if (j == removed_col) {
                    std::advance(this_it, 1);
                    continue;
                }
                *(buffer_it++) = *(this_it++);
            }
        }
        return Matrix<T,N-1>{buffer};
    }

    auto Minor(const uint& i, const uint& j) const -> T {
        return SubMatrix(i,j).Determinant();
    }

    auto Cofactor(const int i, const int j) const -> T {
        auto isEven = [](const int i, const int j) -> int {
            return (i+j) % 2 == 0 ? 1 : -1;
        };
        return isEven(i,j)*Minor(i,j);
    }

    auto CofactorMatrix() const -> Matrix<T, N> {
        Matrix<T, N> buffer;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                buffer(i,j) = Cofactor(i,j);
            }
        }
        return buffer;
    }

    auto Invertible() const -> bool {
        return Determinant() != (T)0;
    }

    auto Inverse() const -> Matrix<T, N> {
        const T det{Determinant()};
        return CofactorMatrix().Transpose() * (1/det);
    }
};

using Matrix2f = Matrix<float, 2>;
using Matrix3f = Matrix<float, 3>;
using Matrix4f = Matrix<float, 4>;

#include <iostream>

template<typename T, std::size_t N>
auto operator<<(std::ostream& os, const Matrix<T, N>& mat) -> std::ostream& {
    for (uint ij=0; ij<N*N; ++ij) {
        os << mat(ij) << ' ';
    }
    return os;
}

template<typename T, std::size_t N>
auto Identity() -> Matrix<T, N> {
    Matrix<T, N> buffer;
    for (int i=0; i<N; ++i) {
        buffer(i,i) = (T)1;
    }
    return buffer;
}
// template<typename = float, std::size_t = 4> auto Identity() -> Matrix<float, 4>;

// auto Identity4f() -> Matrix4f;