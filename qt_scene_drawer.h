#ifndef QTSCENEDRAWER_H
#define QTSCENEDRAWER_H

#include <QGraphicsScene>
#include <QPen>
#include <QColor>

#include "scene_drawer_base.h"
#include "figure.h"
#include "edge.h"
#include "vertex.h"

class QtSceneDrawer: public SceneDrawerBase {
private:
    QGraphicsScene* qScene;
    void paintSegment(Vertex& vert1, Vertex& vert2);
public:
    explicit QtSceneDrawer(QGraphicsScene* scene);
    void drawScene(Scene& scene) override;
    void clear() override;
    void drawAxes(float axisLength);
};

#endif // QTSCENEDRAWER_
