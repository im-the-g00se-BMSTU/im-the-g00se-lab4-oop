#ifndef VERTEX_H
#define VERTEX_H

#include "point3d.h"
#include "scene_object.h"

class Vertex: public SceneObject {
private:
    Point3D position;
public:
    Vertex(Point3D point) : position(point) {}
    Point3D& getPosition() {
        return position;
    }

    void transform(TransformMatrix& transformMatrix) override {
        position = transformMatrix.transformPoint(position);
    }
};

#endif // VERTEX_H
