#ifndef FACADE_H
#define FACADE_H

#include <cmath>

#include "normalizationparameters.h"
#include "base_file_reader.h"
#include "constants.h"
#include "scene_drawer_base.h"
#include "facade_operation_result.h"
#include "transform_matrix_builder.h"
#include "scene.h"
#include "transform_matrix_builder.h"

class Facade {
private:
    std::unique_ptr<BaseFileReader> fileReader;
    std::unique_ptr<SceneDrawerBase> sceneDrawer;
    std::unique_ptr<Scene> scene;
    Point3D currentMove = {Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE};
    Point3D currentScale = {Constants::DEFAULT_SCALE, Constants::DEFAULT_SCALE, Constants::DEFAULT_SCALE};
    void applyToScene(TransformMatrix& matrix);
public:
    Facade(std::unique_ptr<BaseFileReader> reader, std::unique_ptr<SceneDrawerBase> drawer);
    void transformScene(TransformMatrix& matrix);
    FacadeOperationResult loadScene(std::filesystem::path& path, NormalizationParameters& normalizattionParameters);
    FacadeOperationResult drawScene();
    FacadeOperationResult moveScene(float moveX, float moveY, float moveZ);
    FacadeOperationResult rotateScene(float rotateX, float rotateY, float rotateZ);
    FacadeOperationResult scaleScene(float scaleX, float scaleY, float scaleZ);

};

#endif // FACADE_H
