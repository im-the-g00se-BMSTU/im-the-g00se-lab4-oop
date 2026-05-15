#include "facade.h"

bool isWholeStep(double step) {
    return std::isfinite(step) && step >= 1.0 && std::floor(step) == step;
}

Facade::Facade(std::unique_ptr<BaseFileReader> reader, std::unique_ptr<SceneDrawerBase> drawer)
    : fileReader(std::move(reader)), sceneDrawer(std::move(drawer)) {}

FacadeOperationResult Facade::loadScene(std::filesystem::path& path, NormalizationParameters& params) {
    currentMove = {Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE, Constants::DEFAULT_VALUE};
    currentScale = {Constants::DEFAULT_SCALE, Constants::DEFAULT_SCALE, Constants::DEFAULT_SCALE};
    FacadeOperationResult result = FacadeOperationResult::success();

    if (!(params.max > params.min && isWholeStep(params.dxStep) && isWholeStep(params.dyStep)))
        result = FacadeOperationResult::invalidParams();
    else if (path.extension() != ".csv")
        result = FacadeOperationResult::invalidFile();
    else {
        scene = fileReader->readScene(path, params);

        if (!scene || scene->getFigures().empty())
            result = FacadeOperationResult::invalidFile();
        else {
            result = rotateScene(Constants::INITIAL_X_ROTATION, Constants::INITIAL_Y_ROTATION, Constants::INITIAL_Z_ROTATION);
            if (result.isSuccess())
                result = scaleScene(Constants::INITIAL_SCALE, Constants::INITIAL_SCALE, Constants::INITIAL_SCALE);
        }
    }

    return result;
}

FacadeOperationResult Facade::drawScene() {
    FacadeOperationResult result = FacadeOperationResult::success();

    if (!scene || !sceneDrawer)
        result = FacadeOperationResult::drawError();
    else {
        sceneDrawer->clear();
        sceneDrawer->drawScene(*scene);
    }

    return result;
}

FacadeOperationResult Facade::moveScene(float moveX, float moveY, float moveZ) {
    FacadeOperationResult result = FacadeOperationResult::success();

    if (!scene)
        result = FacadeOperationResult::invalidData();
    else {
        float newX = currentMove.x + moveX;
        float newY = currentMove.y + moveY;
        float newZ = currentMove.z + moveZ;

        if (std::abs(newX) > Constants::MAX_TRANSLATE ||
            std::abs(newY) > Constants::MAX_TRANSLATE ||
            std::abs(newZ) > Constants::MAX_TRANSLATE)
            result = FacadeOperationResult::translationLimit();
        else {
            currentMove.x = newX;
            currentMove.y = newY;
            currentMove.z = newZ;

            auto moveMatrix = TransformMatrixBuilder::createMoveMatrix(moveX, moveY, moveZ);
            scene->transformFigures(moveMatrix);
        }
    }

    return result;
}

FacadeOperationResult Facade::rotateScene(float rotateX, float rotateY, float rotateZ) {
    FacadeOperationResult result = FacadeOperationResult::success();

    if (!scene)
        result = FacadeOperationResult::invalidData();
    else {
        float radX = rotateX * (Constants::PI / 180.0);
        float radY = rotateY * (Constants::PI / 180.0);
        float radZ = rotateZ * (Constants::PI / 180.0);

        auto rotationMatrix = TransformMatrixBuilder::createRotationMatrix(radX, radY , radZ);
        scene->transformFigures(rotationMatrix);
    }

    return result;
}

FacadeOperationResult Facade::scaleScene(float scaleX, float scaleY, float scaleZ) {
    FacadeOperationResult result = FacadeOperationResult::success();

    if (!scene)
        result = FacadeOperationResult::invalidData();
    else {
        float newScaleX = currentScale.x * scaleX;
        float newScaleY = currentScale.y * scaleY;
        float newScaleZ = currentScale.z * scaleZ;

        if (newScaleX < Constants::MIN_SCALE || newScaleX > Constants::MAX_SCALE ||
            newScaleY < Constants::MIN_SCALE || newScaleY > Constants::MAX_SCALE ||
            newScaleZ < Constants::MIN_SCALE || newScaleZ > Constants::MAX_SCALE)
            result = FacadeOperationResult::scaleLimit();
        else {
            currentScale.x = newScaleX;
            currentScale.y = newScaleY;
            currentScale.z = newScaleZ;

            auto scaleMatrix = TransformMatrixBuilder::createScaleMatrix(scaleX, scaleY, scaleZ);
            scene->transformFigures(scaleMatrix);
        }
    }

    return result;
}
