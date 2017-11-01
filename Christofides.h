//
// Created by Isabelle Hallman on 2017-11-01.
//

#ifndef AVALGPROJ1_CHRISTOFIDES_H
#define AVALGPROJ1_CHRISTOFIDES_H
#include <iostream>
#include "Node.h"
#include <vector>

struct EdgeK {
    int to, from;
    float weight;
};

struct Graph {
    int v, e;
    struct EdgeK* edges;
};

struct Vertix {
    float x, y;
    int degree;
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
    explicit Christofides(std::vector<Node>& cities);
private:
    void kruskal(); //Find minimum spanning tree
    void createUnevenVset();
    Graph perfectMatching();
    void hierholzer(); //Find eulerian tour
    void addEdges();
    std::vector<Node>& cities;
    Graph fullGraph, newGraph;
    Sets nodeSets;

};


#endif //AVALGPROJ1_CHRISTOFIDES_H
