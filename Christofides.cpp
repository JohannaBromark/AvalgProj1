//
// Created by Isabelle Hallman on 2017-11-01.
//

#include "Christofides.h"
#include <iostream>
#include <vector>
#include <algorithm>

int compareEdge(const void *s1, const void *s2)
{
    struct EdgeK *e1 = (struct EdgeK *) s1;
    struct EdgeK *e2 = (struct EdgeK *) s2;
    return int(e1->weight - e2->weight);
}

Christofides::Christofides(std::vector<Node>& citiesIn) : cities(citiesIn), nodeSets(citiesIn.size()) {
    Graph fullGraph;
    fullGraph.v = (int) cities.size();
    fullGraph.e = fullGraph.v*(fullGraph.v-1)/2;
    fullGraph.edges = new EdgeK[fullGraph.e];
    addEdges();
    kruskal();

}

void Christofides::addEdges(){
    int counter = 0;
    for (int i = 0; i < cities.size() - 1; i++){
        for (int j = i + 1; j < cities.size(); j++){
            fullGraph.edges[counter].from = i;
            fullGraph.edges[counter].to = j;
            fullGraph.edges[counter].weight = cities.at(i).calcDistance(cities.at(j));
            counter++;
        }
        counter++;
    }
}

void Christofides::kruskal(){
    //Create minimal spanning tree through Kruskal's algorithm
    struct EdgeK result[fullGraph.v - 1];
    std::qsort(fullGraph.edges, fullGraph.e, sizeof(struct EdgeK), compareEdge);

    int i, n;
    for (i = n = 0; i < fullGraph.e && n < fullGraph.v - 1; i++) {
        int u = fullGraph.edges[i].from; int v = fullGraph.edges[i].to;
        if (nodeSets.findParent(u) != nodeSets.findParent(v)) {
            result[n] = fullGraph.edges[i];
            nodeSets.addDegree(u);
            nodeSets.addDegree(v);
            n++;
            nodeSets.unite(v, u);
        }
    }
}

