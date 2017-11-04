//
// Created by Isabelle Hallman on 2017-11-01.
//

#ifndef AVALGPROJ1_CHRISTOFIDES_H
#define AVALGPROJ1_CHRISTOFIDES_H

#include <iostream>
#include "Node.h"
#include <vector>
#include <list>
#include <math.h>

struct EdgeK {
    int to = 0;
    int from = 0;
    double weight;
};

struct Graph {
    int v, e;
    struct EdgeK* edges;
};

struct Town {
    double x, y;
    int index;

    Town(double xIn, double yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
    }

    int calcDistance(Town other) {
        return (int) sqrt(pow( ( x - other.getX() ), 2 ) + pow( ( y - other.getY() ), 2 ));
    }

    double getX(){
        return x;
    }

    double getY(){
        return y;
    }
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
        if (vertix < n) {
            degree[vertix] += 1;
        }
    }

    void unite(int x, int y) {
        int xParent = findParent(x);
        int yParent = findParent(y);
        if (xParent == yParent) return;
        else if (ranks[xParent] < ranks[yParent]) {
            parents[xParent] = yParent;
            ranks[y] += ranks[x];
        }
        else {
            parents[yParent] = xParent;
            ranks[x] += ranks[y];
        }
    }

    int findParent(int x) {
        if (parents[x] == x) {
            return x;
        }
        else {
            return findParent(parents[x]);
        }
    }
};



class Christofides {

public:
    std::list<int> eulerTour;
    explicit Christofides(std::vector<Town> cities);
    void printTour(std::list<int> inList);
    std::vector<Node> citiesOut;
private:
    void kruskal(); //Find minimum spanning tree
    void perfectMatching(std::vector<std::list<int>>& verticesAdjacency);
    void hierholzer(std::vector<std::list<int>>& verticesAdjacency); //Find eulerian tour
    void addEdges();
    std::vector<Town>& cities;
    Graph fullGraph, kruskalGraph;
    Sets nodeSets;
};


#endif //AVALGPROJ1_CHRISTOFIDES_H
