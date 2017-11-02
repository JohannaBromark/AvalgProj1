#include "Savings.h"
//#include <tuple>


Savings::Savings(Node &hubIn, Node &sNode1In, Node &sNode2In): hub(hubIn), sNode1(sNode1In), sNode2(sNode2In){
    saving = hub.calcDistance(sNode1)+hub.calcDistance(sNode2) - sNode1.calcDistance(sNode2);
}

//Copy-constructor
Savings::Savings(const Savings& s) : hub(s.getHub()), sNode1(std::get<0>(s.getNodes())), sNode2(std::get<1>(s.getNodes())){
    saving = s.getSave();
};

std::tuple<Node&, Node&> Savings::getNodes() const{
    std::tuple<Node&, Node&> returnNodes(sNode1, sNode2);
    return returnNodes;
}

Node& Savings::getHub()const{
    return hub;
}

bool Savings::operator<(Savings& otherSave){
    return saving < otherSave.getSave();
}

bool Savings::operator>(Savings& otherSave){
    return saving > otherSave.getSave();
}

bool Savings::operator =(const Savings& otherSave){
    return saving = otherSave.getSave();
}

float Savings::getSave()const{
    return saving;
}