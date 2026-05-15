#include "touchpad_scene_controller.h"

TouchpadSceneController::TouchpadSceneController(QGraphicsView* controlledView, QObject* parent)
    : QObject(parent), view(controlledView), currentZoom(1.0) {
    if (view) {
        view->installEventFilter(this);
        view->viewport()->installEventFilter(this);
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        view->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    }
}

bool TouchpadSceneController::eventFilter(QObject* watched, QEvent* event) {
    bool isHandled = false;

    if (event->type() == QEvent::Wheel)
        isHandled = handleWheelEvent(static_cast<QWheelEvent*>(event));
    else if (event->type() == QEvent::NativeGesture)
        isHandled = handleNativeGesture(static_cast<QNativeGestureEvent*>(event));

    if (!isHandled)
        isHandled = QObject::eventFilter(watched, event);

    return isHandled;
}

bool TouchpadSceneController::handleWheelEvent(QWheelEvent* event) {
    bool isHandled = true;

    if ((event->modifiers() & Qt::ControlModifier) != 0)
        zoomBy(wheelZoomFactor(event));
    else {
        QPoint delta = event->pixelDelta();

        if (delta.isNull())
            delta = event->angleDelta() / 2;

        if ((event->modifiers() & Qt::ShiftModifier) != 0 && delta.x() == 0)
            delta = QPoint(delta.y(), 0);

        if (delta.isNull())
            isHandled = false;
        else
            panBy(delta);
    }

    if (isHandled)
        event->accept();

    return isHandled;
}

bool TouchpadSceneController::handleNativeGesture(QNativeGestureEvent* event) {
    bool isHandled = false;

    if (event->gestureType() == Qt::ZoomNativeGesture) {
        double factor = 1.0 + event->value();

        if (factor > 0.0) {
            zoomBy(factor);
            isHandled = true;
        }
    }

    if (isHandled)
        event->accept();

    return isHandled;
}

void TouchpadSceneController::panBy(const QPoint& delta) {
    view->horizontalScrollBar()->setValue(view->horizontalScrollBar()->value() - delta.x());
    view->verticalScrollBar()->setValue(view->verticalScrollBar()->value() - delta.y());
}

void TouchpadSceneController::zoomBy(double factor) {
    double nextZoom = clampZoom(currentZoom * factor);
    double appliedFactor = nextZoom / currentZoom;
    currentZoom = nextZoom;
    view->scale(appliedFactor, appliedFactor);
}

double TouchpadSceneController::clampZoom(double zoom) const {
    double clampedZoom = std::max(Constants::MIN_ZOOM, std::min(Constants::MAX_ZOOM, zoom));
    return clampedZoom;
}

double TouchpadSceneController::wheelZoomFactor(const QWheelEvent* event) const {
    int units = event->angleDelta().y();

    if (units == 0)
        units = event->pixelDelta().y();

    double factor = std::pow(1.0 + Constants::WHEEL_ZOOM_STEP, units);
    return factor;
}
