#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "transform_matrix.h"

class SceneObject {
public:
    virtual ~SceneObject() = default;
    virtual void transform(TransformMatrix& transformMatrix) = 0;
};

#endif // SCENEOBJECT_H
