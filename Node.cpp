// in node.cpp
#include "Node.h"

    Node::Node (float xIn, float yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
    }

    std::tuple<float, float> getXY() {
        return std::make_tuple(x, y);
    };

    float calcDistance (Node& otherCity) {
        return sqrt(pow( ( x - std::get<0>(otherCity.getXY()) ), 2 ) + pow( ( y - std::get<1>(otherCity.getXY()) ), 2 ));
    };
