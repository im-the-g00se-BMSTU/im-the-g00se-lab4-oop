#ifndef SCENE_H
#define SCENE_H

#include <filesystem>
#include <memory>
#include <vector>

#include "figure.h"

class Scene {
private:
    std::vector<std::shared_ptr<Figure>> figures;
public:
    std::vector<std::shared_ptr<Figure>>& getFigures() {
        return figures;
    }

    void transformFigures(TransformMatrix& transformMatrix) {
        for (auto& figure : figures)
            figure->transform(transformMatrix);
    }
};

#endif // SCENE_H
