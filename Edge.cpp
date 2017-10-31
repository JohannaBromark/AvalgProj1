#include "Edge.h"
#include <iostream>

Edge::Edge(Node node1in, Node node2in){
    node1 = &node1in;
    node2 = &node2in;
    distance = (*node1).calcDistance(*node2);
}

//Copy-constructor
Edge::Edge(const Edge& e) : node1(&(e.getNode(1))), node2(&(e.getNode(2))){
    distance = e.getDistance();
};

float Edge::getDistance() const{
    return distance;
}

Node& Edge::getNode(int index) const {
    if (index == 2) {
        return *node2;
    }
    else {
        return *node1;
    }
}

bool Edge::operator==(Edge& other) {
    if ( (*node1 == other.getNode(1) && *node2 == other.getNode(2))
         || (*node1 == other.getNode(2) && *node2 == other.getNode(1)) ) {
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