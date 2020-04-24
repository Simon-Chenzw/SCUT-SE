//! @file:Matrix.h

#pragma once
#include <iostream>

class Matrix {
  private:
    double a, b, c, d;

  public:
    Matrix(double = 1, double = 0, double = 0, double = 1);
    ~Matrix();
    Matrix operator+(Matrix) const;
    Matrix operator-(Matrix) const;
    Matrix operator*(Matrix) const;

    Matrix operator*(double)const;
    friend Matrix operator*(double, Matrix);

    Matrix& operator+=(Matrix);
    Matrix& operator-=(Matrix);
    Matrix& operator*=(Matrix);

    bool operator==(Matrix) const;
    bool operator!=(Matrix) const;

    friend std::istream& operator>>(std::istream&, Matrix&);
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
};