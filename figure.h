#ifndef FIGURE_H
#define FIGURE_H

#include <vector>

#include "scene_object.h"
#include "vertex.h"
#include "edge.h"

class Figure: public SceneObject {
private:
    std::vector<Edge> edges;
public:
    Figure(std::vector<Edge>& edges) : edges(edges) {}

    std::vector<Edge>& getEdges() {
        return edges;
    }

    void transform(TransformMatrix& transformMatrix) override {
        for (Edge& edge : edges) {
            edge.getBegin().transform(transformMatrix);
            edge.getEnd().transform(transformMatrix);
        }
    }
};

#endif // FIGURE_H
