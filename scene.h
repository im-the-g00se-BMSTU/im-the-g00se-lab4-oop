#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "figure.h"

class Scene {
private:
    std::vector<Figure> figures;
public:
    std::vector<Figure>& getFigures() {
        return figures;
    }

    void transformFigures(TransformMatrix& transformMatrix) {
        for (auto& figure : figures)
            figure.transform(transformMatrix);
    }
};

#endif // SCENE_H
