//
// Created by Isabelle Hallman on 2017-11-01.
//

#ifndef AVALGPROJ1_CHRISTOFIDES_H
#define AVALGPROJ1_CHRISTOFIDES_H
#include <iostream>
#include "Node.h"

struct EdgeK {
    int to, from;
    float weight;
};

struct Graph {
    int v, e;
    struct EdgeK* edges;
};

struct Set {
    struct EdgeK* edges;
};

class Christofides {
    explicit Christofides(std::vector<Node>& cities);
private:
    void kruskal();
    void addEdges();
    std::vector<Node>& cities;
    Graph fullGraph;

};


#endif //AVALGPROJ1_CHRISTOFIDES_H
