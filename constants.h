#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    constexpr int MATRIX_SIZE = 4;
    constexpr double PI = 3.141592653589793;
    constexpr char SEPARATOR = ',';
    constexpr float DEFAULT_VALUE  = 0.0;
    constexpr float COEFFICIENT_PROJECTION_X = 0.5;
    constexpr float SCENE_RECT_SIZE = 1000;

    constexpr float LINE_WIDTH = 1.0;
    constexpr float AXIS_WIDTH = 2;
    constexpr float AXIS_LENGTH = 200;

    constexpr float UNIT_OF_ROTATION = 30.0;
    constexpr float UNIT_OF_TRANSLATE = 20.0;
    constexpr float MAX_TRANSLATE = 200.0;

    constexpr double MIN_ZOOM = 0.2;
    constexpr double MAX_ZOOM = 20.0;
    constexpr double WHEEL_ZOOM_STEP = 0.0015;

    constexpr float INITIAL_SCALE = 8.0;
    constexpr float INITIAL_X_ROTATION = -90.0;
    constexpr float INITIAL_Y_ROTATION = 0.0;
    constexpr float INITIAL_Z_ROTATION = -90.0;

    constexpr float DEFAULT_SCALE = 1.0;
    constexpr float MIN_SCALE = 4.0;
    constexpr float MAX_SCALE = 32.0;
    constexpr float COEFFICIENT_SCALE_IN = 1.2;
    constexpr float COEFFICIENT_SCALE_OUT = 0.9;
}

#endif // CONSTANTS_H
