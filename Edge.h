
#ifndef _Edge_h
#define _Edge_h
#include "Node.h"

class Edge {
    public:
        Edge(Node& node1, Node& node2);
        float getDistance() const;
        bool operator==(Edge& other);
        bool operator>(Edge& other);
        bool operator<(Edge& other);
        Node& getToNode();
        Node& getFromNode();

    private:
        float distance;
        Node& to;
        Node& from;
};


#endif //_Edge_h
