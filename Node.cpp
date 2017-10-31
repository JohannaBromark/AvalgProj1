#include "Node.h"
using namespace std;

    Node::Node (float xIn, float yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
        twoCon2Hub = false;
        oneCon2Hub = false;
        neighbor1 = NULL;
        neighbor2 = NULL;
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

    void Node::addNeighbor(Node *newNeighbor){
        if (neighbor1 == 0){
            neighbor1 = newNeighbor;
            twoCon2Hub = false;
        } 
        else {
            neighbor2 = newNeighbor;
            oneCon2Hub = false;
        }
    }

    bool Node::isConnectedToHub(){
        //A node is connected to hub iff it has at least one connection to the hub. 
        return oneCon2Hub;
    }

    bool Node::isOnlyConnectedToHub(){
        return twoCon2Hub;
    }

    void Node::connectToHub(Node *hubNode){
        neighbor1 = hubNode;
        neighbor2 = hubNode;
        oneCon2Hub, twoCon2Hub = true;
    }

    Node* Node::getNeighbor(int neighborNum){
        if (neighborNum == 1){
            return neighbor1;
        }
        if (neighborNum == 2){
            return neighbor2;
        }
        return 0; //In case of wrong index 
    }

    void Node::changeNeighbor(int neighborN, Node *aNewNeighbor){
        if (neighborN == 1){
            neighbor1 = aNewNeighbor;
        }
        if (neighborN == 2){
            neighbor2 = aNewNeighbor;
        }
    }

    int Node::getNeighborInd(Node& neighbor){
        if (neighbor == *neighbor1) {
            return 1;
        } else if (neighbor == *neighbor2){
            return 2;
        } else{
            return 0;
        }
    }
    