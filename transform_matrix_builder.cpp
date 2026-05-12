#include "transform_matrix_builder.h"

namespace {
float cosine(float angle) {
    return static_cast<float>(std::cos(angle));
}

float sine(float angle) {
    return static_cast<float>(std::sin(angle));
}
}

TransformMatrix TransformMatrixBuilder::createMoveMatrix(float moveX, float moveY, float moveZ) {
    float mat[Constants::MATRIX_SIZE][Constants::MATRIX_SIZE] =
        {{1, 0, 0, moveX},
        {0, 1, 0, moveY},
        {0, 0, 1, moveZ},
        {0, 0, 0, 1}};

    TransformMatrix transformMatrix = mat;

    return transformMatrix;
}

TransformMatrix TransformMatrixBuilder::createRotationMatrix(float rotateX, float rotateY, float rotateZ) {
    float matRotateX[Constants::MATRIX_SIZE][Constants::MATRIX_SIZE] =
        {{1, 0, 0, 0},
        {0, cosine(rotateX), -sine(rotateX), 0},
        {0, sine(rotateX), cosine(rotateX), 0},
        {0, 0, 0, 1}};

    float matRotateY[Constants::MATRIX_SIZE][Constants::MATRIX_SIZE] =
        {{cosine(rotateY), 0, sine(rotateY), 0},
        {0, 1, 0, 0},
        {-sine(rotateY), 0, cosine(rotateY), 0},
        {0, 0, 0, 1}};

    float matRotateZ[Constants::MATRIX_SIZE][Constants::MATRIX_SIZE] =
        {{cosine(rotateZ), -sine(rotateZ), 0, 0},
        {sine(rotateZ), cosine(rotateZ), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    TransformMatrix transformMatrixX = matRotateX;
    TransformMatrix transformMatrixY = matRotateY;
    TransformMatrix transformMatrixZ = matRotateZ;

    return transformMatrixX*transformMatrixY*transformMatrixZ;
}

TransformMatrix TransformMatrixBuilder::createScaleMatrix(float scaleX, float scaleY, float scaleZ) {
    float mat[Constants::MATRIX_SIZE][Constants::MATRIX_SIZE] =
        {{scaleX, 0, 0, 0},
        {0, scaleY, 0, 0},
        {0, 0, scaleZ, 0},
        {0, 0, 0, 1}};

    TransformMatrix transformMatrix = mat;

    return transformMatrix;
}
