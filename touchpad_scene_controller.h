#ifndef TOUCHPAD_SCENE_CONTROLLER_H
#define TOUCHPAD_SCENE_CONTROLLER_H

#include <QObject>
#include <QPoint>
#include <QGraphicsView>
#include <QNativeGestureEvent>
#include <QScrollBar>
#include <QWheelEvent>

#include <cmath>

#include "constants.h"

class TouchpadSceneController : public QObject {
public:
    explicit TouchpadSceneController(QGraphicsView* controlledView, QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    QGraphicsView* view;
    double currentZoom;

    bool handleWheelEvent(QWheelEvent* event);
    bool handleNativeGesture(QNativeGestureEvent* event);
    void panBy(const QPoint& delta);
    void zoomBy(double factor);
    double clampZoom(double zoom) const;
    double wheelZoomFactor(const QWheelEvent* event) const;
};

#endif // TOUCHPAD_SCENE_CONTROLLER_H
