#include "qt_scene_drawer.h"

QtSceneDrawer::QtSceneDrawer(QGraphicsScene* scene) : qScene(scene){}

void QtSceneDrawer::drawScene(Scene& scene) {
    if (!qScene)
        return;

    drawAxes(Constants::AXIS_LENGTH);

    for (auto& figure : scene.getFigures()) {
        for (auto& edge : figure->getEdges()) {
            auto& vert1 = edge.getBegin();
            auto& vert2 = edge.getEnd();
            paintSegment(vert1, vert2);
        }
    }
}

void QtSceneDrawer::paintSegment(Vertex& vert1, Vertex& vert2) {
    QPen pen(QColor(100, 200, 255));
    pen.setWidthF(Constants::LINE_WIDTH);
    qScene->addLine(vert1.getPosition().x, -vert1.getPosition().y, vert2.getPosition().x, -vert2.getPosition().y, pen);
}

void QtSceneDrawer::drawAxes(float axisLength) {
    if (!qScene)
        return;

    QPen xPen(Qt::red);
    xPen.setWidthF(Constants::AXIS_WIDTH);
    qScene->addLine(0, 0, axisLength, 0, xPen);

    QPen yPen(Qt::green);
    yPen.setWidthF(Constants::AXIS_WIDTH);
    qScene->addLine(0, 0, 0, -axisLength, yPen);

    QPen zPen(Qt::blue);
    zPen.setWidthF(Constants::AXIS_WIDTH);
    qScene->addLine(0, 0, 0, axisLength * 0.2, zPen);
}

void QtSceneDrawer::clear() {
    if (qScene)
        qScene->clear();
}
