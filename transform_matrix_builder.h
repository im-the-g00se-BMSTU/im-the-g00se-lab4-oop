#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H

#include "transform_matrix.h"
#include "constants.h"
#include <cmath>

class TransformMatrixBuilder {
public:
    static TransformMatrix createRotationMatrix(float rotateX, float rotateY, float rotateZ);
    static TransformMatrix createScaleMatrix(float scaleX, float scaleY, float scaleZ);
    static TransformMatrix createMoveMatrix(float moveX, float moveY, float moveZ);
};

#endif // TRANSFORMMATRIXBUILDER_H
