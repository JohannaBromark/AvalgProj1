#include "Node.h"
using namespace std;

    Node::Node (float xIn, float yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
    }

    tuple<float, float> Node::getXY() {
        return std::make_tuple(x, y);
    };

    float Node::calcDistance (Node& otherCity) {
        return sqrt(pow( ( x - std::get<0>(otherCity.getXY()) ), 2 ) + pow( ( y - std::get<1>(otherCity.getXY()) ), 2 ));
    };

    int Node::getIndex() {
        return index;
    }

    bool Node::operator== (Node& other) {
        return index == other.getIndex();
    }
