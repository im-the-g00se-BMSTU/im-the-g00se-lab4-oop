#include "facade.h"

namespace {
bool isWholeStep(double step) {
    return std::isfinite(step) && step >= 1.0 && std::floor(step) == step;
}

bool canUseParams(const NormalizationParameters& params) {
    return params.max > params.min && isWholeStep(params.dxStep) && isWholeStep(params.dyStep);
}

bool isCsvPath(const std::filesystem::path& path) {
    return path.extension() == ".csv";
}
}

Facade::Facade(std::unique_ptr<BaseFileReader> reader, std::unique_ptr<SceneDrawerBase> drawer)
    : fileReader(std::move(reader)), sceneDrawer(std::move(drawer)) {}

FacadeOperationResult Facade::loadScene(std::filesystem::path& path, NormalizationParameters& normalizattionParameters) {
    currentMove = {Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE};
    currentScale = {Constants::DEFAULT_SCALE, Constants::DEFAULT_SCALE, Constants::DEFAULT_SCALE};

    if (!canUseParams(normalizattionParameters))
        return  FacadeOperationResult::invalidParams();

    if (!isCsvPath(path))
        return FacadeOperationResult::invalidFile();

    scene = fileReader->readScene(path, normalizattionParameters);

    if (!scene || scene->getFigures().empty())
        return FacadeOperationResult::invalidFile();

    return FacadeOperationResult::success();
}

FacadeOperationResult Facade::drawScene() {
    if (!scene || !sceneDrawer)
        return FacadeOperationResult::drawError();

    sceneDrawer->clear();
    sceneDrawer->drawScene(*scene);

    return FacadeOperationResult::success();
}

FacadeOperationResult Facade::moveScene(float moveX, float moveY, float moveZ) {
    if (!scene)
        return FacadeOperationResult::invalidData();

    float newX = currentMove.x + moveX;
    float newY = currentMove.y + moveY;
    float newZ = currentMove.z + moveZ;

    if (std::abs(newX) > Constants::MAX_TRANSLATE ||
        std::abs(newY) > Constants::MAX_TRANSLATE ||
        std::abs(newZ) > Constants::MAX_TRANSLATE)
        return FacadeOperationResult::translationLimit();

    currentMove.x = newX;
    currentMove.y = newY;
    currentMove.z = newZ;

    auto moveMatrix = TransformMatrixBuilder::createMoveMatrix(moveX, moveY, moveZ);
    applyToScene(moveMatrix);

    return FacadeOperationResult::success();
}

FacadeOperationResult Facade::rotateScene(float rotateX, float rotateY, float rotateZ) {
    if (!scene)
        return FacadeOperationResult::invalidData();

    float radX = rotateX * (Constants::PI / 180.0);
    float radY = rotateY * (Constants::PI / 180.0);
    float radZ = rotateZ * (Constants::PI / 180.0);

    auto rotationMatrix = TransformMatrixBuilder::createRotationMatrix(radX, radY , radZ);
    applyToScene(rotationMatrix);

    return FacadeOperationResult::success();
}

FacadeOperationResult Facade::scaleScene(float scaleX, float scaleY, float scaleZ) {
    if (!scene)
        return FacadeOperationResult::invalidData();

    float newScaleX = currentScale.x * scaleX;
    float newScaleY = currentScale.y * scaleY;
    float newScaleZ = currentScale.z * scaleZ;

    if (newScaleX < Constants::MIN_SCALE || newScaleX > Constants::MAX_SCALE ||
        newScaleY < Constants::MIN_SCALE || newScaleY > Constants::MAX_SCALE ||
        newScaleZ < Constants::MIN_SCALE || newScaleZ > Constants::MAX_SCALE)
        return FacadeOperationResult::scaleLimit();

    currentScale.x = newScaleX;
    currentScale.y = newScaleY;
    currentScale.z = newScaleZ;

    auto scaleMatrix = TransformMatrixBuilder::createScaleMatrix(scaleX, scaleY, scaleZ);
    applyToScene(scaleMatrix);

    return FacadeOperationResult::success();
}

void Facade::applyToScene(TransformMatrix& matrix) {
    if (scene)
        scene->transformFigures(matrix);
}

void Facade::transformScene(TransformMatrix& matrix) {
    applyToScene(matrix);
}
