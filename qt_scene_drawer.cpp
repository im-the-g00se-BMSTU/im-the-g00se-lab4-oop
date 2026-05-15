#include "qt_scene_drawer.h"

QPointF projectPoint(const Point3D& point) {
    constexpr float zProjection = 0.5;
    QPointF projected(point.x + point.z * zProjection, -point.y + point.z * zProjection);
    return projected;
}

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
    QPointF begin = projectPoint(vert1.getPosition());
    QPointF end = projectPoint(vert2.getPosition());
    qScene->addLine(begin.x(), begin.y(), end.x(), end.y(), pen);
}

void QtSceneDrawer::drawAxes(float axisLength) {
    if (!qScene)
        return;

    QPointF origin = projectPoint(Point3D(0, 0, 0));
    QPointF xEnd = projectPoint(Point3D(axisLength, 0, 0));
    QPointF yEnd = projectPoint(Point3D(0, axisLength, 0));
    QPointF zEnd = projectPoint(Point3D(0, 0, axisLength));

    QPen xPen(Qt::red);
    xPen.setWidthF(Constants::AXIS_WIDTH);
    qScene->addLine(origin.x(), origin.y(), xEnd.x(), xEnd.y(), xPen);

    QPen yPen(Qt::green);
    yPen.setWidthF(Constants::AXIS_WIDTH);
    qScene->addLine(origin.x(), origin.y(), yEnd.x(), yEnd.y(), yPen);

    QPen zPen(Qt::blue);
    zPen.setWidthF(Constants::AXIS_WIDTH);
    qScene->addLine(origin.x(), origin.y(), zEnd.x(), zEnd.y(), zPen);
}

void QtSceneDrawer::clear() {
    if (qScene)
        qScene->clear();
}
