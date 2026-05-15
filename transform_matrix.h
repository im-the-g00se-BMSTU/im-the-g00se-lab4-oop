#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "point3d.h"
#include "constants.h"
#include <cstddef>

class TransformMatrix {
private:
    float matrix[Constants::MATRIX_SIZE][Constants::MATRIX_SIZE];
public:
    TransformMatrix(float mat[Constants::MATRIX_SIZE][Constants::MATRIX_SIZE]);
    TransformMatrix operator*(const TransformMatrix& transformMatrix) const;
    Point3D transformPoint(const Point3D& point3D) const;
};

#endif // TRANSFORMMATRIX_H
