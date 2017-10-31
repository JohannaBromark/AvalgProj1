#include "Node.h"
using namespace std;

    Node::Node (float xIn, float yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
        neighbor1 = -1;
        neighbor2 = -1;
        connectedHub = false;
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

    void Node::addNeighbor(int i){
        if (neighbor1 == -1){
            neighbor1 = i;
            connectedHub = false;
        } 
        else {
            neighbor2 = i;
        }
    }

    bool Node::isConnectedToHub(){
        //A node is connected to hub iff it has both connections to the hub. 
        return connectedHub;
    }

    void Node::connectToHub(int hubIndex){
        neighbor1 = hubIndex;
        neighbor2 = hubIndex;
        connectedHub = true;    
    }

    int Node::getNeighbourIndex(int neighborNum){
        if (neighborNum == 1){
            return neighbor1;
        }
        if (neighborNum == 2){
            return neighbor2;
        }
        return -1; //In case of 
    }