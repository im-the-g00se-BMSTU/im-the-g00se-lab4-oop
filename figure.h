#ifndef FIGURE_H
#define FIGURE_H

#include <vector>

#include "scene_object.h"
#include "vertex.h"
#include "edge.h"

class Figure: public SceneObject {
private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
public:
    Figure(std::vector<Vertex>& verts, std::vector<Edge>& edges) : vertices(verts), edges(edges) {}

    std::vector<Vertex>& getVertices() {
        return vertices;
    }

    std::vector<Edge>& getEdges() {
        return edges;
    }

    void transform(TransformMatrix& transformMatrix) override {
        for (Vertex& vertex : vertices)
            vertex.transform(transformMatrix);

        for (Edge& edge : edges) {
            edge.getBegin().transform(transformMatrix);
            edge.getEnd().transform(transformMatrix);
        }
    }
};

#endif // FIGURE_H
