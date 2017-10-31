
#ifndef _Edge_h
#define _Edge_h
#include "Node.h"

class Edge {
public:
    Edge(Node node1in, Node node2in);
    Edge(const Edge& e);
    float getDistance() const;
    bool operator==(Edge& other);
    bool operator>(Edge& other);
    bool operator<(Edge& other);
    Node& getNode(int index) const;


private:
    float distance;
    Node* node1;
    Node* node2;
};


#endif //_Edge_h

