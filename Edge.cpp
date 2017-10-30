//
// Created by Isabelle Hallman on 2017-10-30.
//

#include "Edge.h"
#include <iostream>

Edge::Edge(Node& node1, Node& node2) : to(node1), from(node2) {
    distance = node1.calcDistance(node2);
}

float Edge::getDistance() const{
    return distance;
}

Node& Edge::getToNode() {
    return to;
}

Node& Edge::getFromNode() {
    return from;
}

bool Edge::operator==(Edge& other) {
    if ( (to == other.getToNode() && from == other.getFromNode())
         || (to == other.getFromNode() && from == other.getToNode()) ) {
        return true;
    }
    else {
        return false;
    }
}

bool Edge::operator>(Edge& other) {
    return distance > other.getDistance();
}

bool Edge::operator<(Edge& other) {
    return distance < other.getDistance();
}