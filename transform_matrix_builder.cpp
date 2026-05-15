#include "transform_matrix_builder.h"

TransformMatrix TransformMatrixBuilder::createMoveMatrix(float moveX, float moveY, float moveZ) {
    TransformMatrix::MatrixData matrix = {{
        {{1, 0, 0, moveX}},
        {{0, 1, 0, moveY}},
        {{0, 0, 1, moveZ}},
        {{0, 0, 0, 1}}
    }};

    return TransformMatrix(matrix);
}

TransformMatrix TransformMatrixBuilder::createRotationMatrix(float rotateX, float rotateY, float rotateZ) {
    TransformMatrix::MatrixData matrixRotateX = {{
        {{1, 0,                 0,                  0}},
        {{0, std::cos(rotateX), -std::sin(rotateX), 0}},
        {{0, std::sin(rotateX), std::cos(rotateX),  0}},
        {{0, 0,                 0,                  1}}
    }};

    TransformMatrix::MatrixData matrixRotateY = {{
        {{std::cos(rotateY),  0, std::sin(rotateY), 0}},
        {{0,                  1, 0,                 0}},
        {{-std::sin(rotateY), 0, std::cos(rotateY), 0}},
        {{0,                  0, 0,                 1}}
    }};

    TransformMatrix::MatrixData matrixRotateZ = {{
        {{std::cos(rotateZ), -std::sin(rotateZ), 0, 0}},
        {{std::sin(rotateZ), std::cos(rotateZ),  0, 0}},
        {{0,                 0,                  1, 0}},
        {{0,                 0,                  0, 1}}
    }};

    TransformMatrix transformMatrixX(matrixRotateX);
    TransformMatrix transformMatrixY(matrixRotateY);
    TransformMatrix transformMatrixZ(matrixRotateZ);

    return transformMatrixX*transformMatrixY*transformMatrixZ;
}

TransformMatrix TransformMatrixBuilder::createScaleMatrix(float scaleX, float scaleY, float scaleZ) {
    TransformMatrix::MatrixData matrix = {{
        {{scaleX, 0,      0,      0}},
        {{0,      scaleY, 0,      0}},
        {{0,      0,      scaleZ, 0}},
        {{0,      0,      0,      1}}
    }};

    return TransformMatrix(matrix);
}
