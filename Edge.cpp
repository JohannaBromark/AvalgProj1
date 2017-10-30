//
// Created by Isabelle Hallman on 2017-10-30.
//

#include "Edge.h"
#include "Node.h"
#include <iostream>

    Edge::Edge(Node& node1, Node& node2) : to(node1), from(node2) {
        distance = node1.calcDistance(node2);
    }

    float Edge::getDistance() {
        return distance;
    }

    Node& Edge::getToNode() {
        return to;
    }

    Node& Edge::getFromNode() {
        return from;
    }

    bool operator==(Edge& other) {
        if (to == other.getToNode() && from == other.getFromNode()) {
            return true;
        }
        else if (to == other.getFromNode() && from == other.getToNode()) {
            return true;
        }
        else {
            return false;
        }
    }