#include "transform_matrix.h"

TransformMatrix::TransformMatrix(const MatrixData& matrix) : matrix(matrix) {}

TransformMatrix TransformMatrix::operator *(const TransformMatrix& transformMatrix) const {
    MatrixData matrixProduct = {};

    for (size_t i = 0; i < Constants::MATRIX_SIZE; i++) {
        for (size_t j = 0; j < Constants::MATRIX_SIZE ;j++) {
            for (size_t k = 0; k < Constants::MATRIX_SIZE; k++)
                matrixProduct[i][j] += this->matrix[i][k] * (transformMatrix.matrix[k][j]);
        }
    }

    return TransformMatrix(matrixProduct);
}

Point3D TransformMatrix::transformPoint(const Point3D& point) const {
    float x = matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.z + matrix[0][3];
    float y = matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.z + matrix[1][3];
    float z = matrix[2][0] * point.x + matrix[2][1] * point.y + matrix[2][2] * point.z + matrix[2][3];

    return Point3D{x, y, z};
}
