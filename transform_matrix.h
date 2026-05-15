#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "point3d.h"
#include "constants.h"
#include <array>
#include <cstddef>

class TransformMatrix {
public:
    using MatrixData = std::array<std::array<float, Constants::MATRIX_SIZE>, Constants::MATRIX_SIZE>;

private:
    MatrixData matrix;

public:
    explicit TransformMatrix(const MatrixData& matrix);
    TransformMatrix operator*(const TransformMatrix& transformMatrix) const;
    Point3D transformPoint(const Point3D& point3D) const;
};

#endif // TRANSFORMMATRIX_H
