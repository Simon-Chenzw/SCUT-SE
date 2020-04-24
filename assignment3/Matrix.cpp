//! @file:Matrix.cpp

#include "Matrix.h"

Matrix::Matrix(double _a, double _b, double _c, double _d)
      : a(_a), b(_b), c(_c), d(_d) {}

Matrix::~Matrix() = default;

Matrix Matrix::operator+(Matrix M) const {
    return {a + M.a, b + M.b, c + M.c, d + M.d};
}

Matrix Matrix::operator-(Matrix M) const {
    return {a - M.a, b - M.b, c - M.c, d - M.d};
}

Matrix Matrix::operator*(Matrix M) const {
    return {a * M.a + b * M.c, a * M.b + b * M.d, c * M.a + d * M.c,
            c * M.b + d * M.d};
}

Matrix Matrix::operator*(double i) const {
    return {a * i, b * i, c * i, d * i};
}

Matrix operator*(double i, Matrix M) {
    return {i * M.a, i * M.b, i * M.c, i * M.d};
}

Matrix& Matrix::operator+=(Matrix M) {
    a += M.a;
    b += M.b;
    c += M.c;
    d += M.d;
    return *this;
}

Matrix& Matrix::operator-=(Matrix M) {
    a -= M.a;
    b -= M.b;
    c -= M.c;
    d -= M.d;
    return *this;
}

Matrix& Matrix::operator*=(Matrix M) { return *this = (*this) * M; }

bool Matrix::operator==(Matrix M) const {
    return a == M.a && b == M.b && c == M.c && d == M.d;
}

bool Matrix::operator!=(Matrix M) const {
    return a != M.a && b != M.b && c != M.c && d != M.d;
}

std::istream& operator>>(std::istream& input, Matrix& M) {
    input >> M.a >> M.b >> M.c >> M.d;
    return input;
}

std::ostream& operator<<(std::ostream& output, const Matrix& M) {
    output << M.a << ' ' << M.b << '\n' << M.c << ' ' << M.d << '\n';
    return output;
}