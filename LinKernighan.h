//
// Created by Isabelle Hallman on 2017-10-30.
//

#ifndef AVALGPROJ1_LINKERNINGHAN_H
#define AVALGPROJ1_LINKERNINGHAN_H
//class Edge;
#include "Edge.h"
class Node;
#include <vector>

class LinKernighan {
public:
    LinKernighan(std::vector<Node>& citiesIn);

private:
    float G;
    std::vector<Node>& cities;
    std::vector<Edge> setOfX;
    std::vector<Edge> setOfY;

    bool checkIfTour(Edge newEdge, int index);

    void generateInitial();

};

#endif //AVALGPROJ1_LINKERNINGHAN_H
