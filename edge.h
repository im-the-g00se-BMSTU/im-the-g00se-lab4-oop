#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

class Edge {
private:
    Vertex begin;
    Vertex end;
public:
    Edge(const Vertex& vertex1, const Vertex& vertex2) : begin(vertex1), end(vertex2) {}

    Vertex& getBegin() {
        return begin;
    }

    Vertex& getEnd() {
        return end;
    }
};

#endif // EDGE_H
