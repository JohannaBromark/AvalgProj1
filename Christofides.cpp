//
// Created by Isabelle Hallman on 2017-11-01.
//

#include "Christofides.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int compareEdge(const void *s1, const void *s2)
{
    struct EdgeK *e1 = (struct EdgeK *) s1;
    struct EdgeK *e2 = (struct EdgeK *) s2;
    return int(e1->weight - e2->weight);
}

Christofides::Christofides(std::vector<Node>& citiesIn) : cities(citiesIn), nodeSets(citiesIn.size()) {
    fullGraph.v = (int) cities.size();
    fullGraph.e = fullGraph.v * (fullGraph.v-1)/2;
    fullGraph.edges = new EdgeK[fullGraph.e];
    addEdges();
    kruskal();
    perfectMatching();
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

Graph Christofides::perfectMatching() {
    std::vector<int> unevenVset = nodeSets.generateUnevenVset();
    int nUnevenV = unevenVset.size();
    int counter, i;
    int n = (int) nUnevenV * (nUnevenV - 1)/2;
    struct EdgeK edges[n];
    struct EdgeK result[nUnevenV / 2];
    for (counter = i = 0; i < nUnevenV-1; i++) {
        for (int j = i + 1; j < nUnevenV; j++) {
            edges[counter].from = i;
            edges[counter].to = j;
            edges[counter].weight = cities.at(i).calcDistance(cities.at(j));
        }
    }
    std::set<int> usedNodes;
    newGraph.v = fullGraph.v; newGraph.e = nUnevenV / 2 + fullGraph.v - 1;
    newGraph.edges = new EdgeK[newGraph.e];

    std::qsort(edges, n, sizeof(struct EdgeK), compareEdge);
    for (counter = i = 0; i < n && counter < nUnevenV/2; i++) {
        if (!usedNodes.count(edges[i].from) && !usedNodes.count(edges[i].to) ){

            usedNodes.insert(edges[i].from); usedNodes.insert(edges[i].to);
            newGraph.edges[newGraph.e - counter] = edges[i];
            counter++;
        }
    }


}

