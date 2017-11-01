#ifndef _Savings_h
#define _Savings_h

#include <tuple>
#include "Node.h"

//class Node;

class Savings{

public:
    Savings(Node& hub, Node& sNode1, Node& sNode2);
    Savings(const Savings& s);
    std::tuple<Node&, Node&> getNodes() const;
    bool operator < (Savings& otherSave);
    bool operator > (Savings& otherSave);
    float getSave()const;
    Node& getHub() const;
private:
    Node& hub;
    Node& sNode1;
    Node& sNode2;
    float saving;
};


#endif