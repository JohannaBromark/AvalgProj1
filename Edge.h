//
// Created by Isabelle Hallman on 2017-10-30.
//

#ifndef AVALGPROJ1_LK_H
#define AVALGPROJ1_LK_H
#include "Node.h"

class Edge {
    public:
        Edge(Node& node1, Node& node2);
        float getDistance();
        bool operator==(Edge& other);
        Node& getToNode();
        Node& getFromNode();
    private:
        float distance;
        Node& to, from;
};


#endif //AVALGPROJ1_LK_H
