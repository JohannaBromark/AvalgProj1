//
// Created by Isabelle Hallman on 2017-11-01.
//

#ifndef AVALGPROJ1_CHRISTOFIDES_H
#define AVALGPROJ1_CHRISTOFIDES_H
#include <iostream>
#include "Node.h"
#include <vector>
#include <list>

struct EdgeK {
    int to = -1;
    int from = -1;
    double weight;
};

struct Graph {
    int v, e;
    struct EdgeK* edges;
};

class Sets {
    int n, *ranks, *parents, *degree;
public:
    Sets(int inN) {
        n = inN;
        ranks = new int[n];
        parents = new int[n];
        degree = new int[n];

        for (int i = 0; i < n; i++) {
            ranks[i] = 1;
            parents[i] = i;
            degree[i] = 0;
        }
    }

    std::vector<int> generateUnevenVset(){
        std::vector<int> unevenVset;
        for (int i = 0; i < n; i++) {
            if (degree[i] % 2 > 0) {
                unevenVset.push_back(i);
            }
        }
        return unevenVset;
    }

    void addDegree(int vertix) {
        degree[vertix] += 1;
    }

    void unite(int x, int y) {
        int xParent = findParent(x);
        int yParent = findParent(y);
        if (xParent == yParent) return;
        else if (ranks[xParent] < ranks[yParent]) {
            parents[x] = parents[y]; ranks[y] += ranks[x];
        }
        else {
            parents[y] = parents[x]; ranks[x] += ranks[y];
        }
    }

    int findParent(int x) {
        if (parents[x] == x) return x;
        else {
            return findParent(parents[x]);
        }
    }
};



class Christofides {

public:
    std::list<int> eulerTour;
    explicit Christofides(std::vector<Node>& cities);
    void printTour(std::list<int> inList);
private:
    void kruskal(struct EdgeK result[]); //Find minimum spanning tree
    void perfectMatching(struct EdgeK result[], std::vector<std::list<int>>& verticesAdjacency);
    void hierholzer(std::vector<std::list<int>> verticesAdjacency); //Find eulerian tour
    void addEdges();
    std::vector<Node>& cities;
    Graph fullGraph, newGraph;
    Sets nodeSets;

};


#endif //AVALGPROJ1_CHRISTOFIDES_H
