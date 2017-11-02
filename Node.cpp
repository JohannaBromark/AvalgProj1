#include "Node.h"
using namespace std;
#include <iostream>

    Node::Node (double xIn, double yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
        //twoCon2Hub = false;
        //oneCon2Hub = false;
        neighbor1 = NULL;
        neighbor2 = NULL;
        visited = false;
    }

    tuple<float, float> Node::getXY() {
        return std::make_tuple(x, y);
    };

    int Node::calcDistance (Node& otherCity) {
        return (int) sqrt(pow( ( x - std::get<0>(otherCity.getXY()) ), 2 ) + pow( ( y - std::get<1>(otherCity.getXY()) ), 2 ));
    };

    int Node::getIndex() {
        return index;
    }

    bool Node::operator== (Node& other) {
        return index == other.getIndex();
    }

    void Node::addNeighborCW(Node *newNeighbor){
        if (twoCon2Hub){
            neighbor1 = newNeighbor;
            twoCon2Hub = false;
        } 
        else {
            neighbor2 = newNeighbor;
            oneCon2Hub = false;
        }
    }

    void Node::addNeighbor(Node* newNeighbor){
        if (neighbor1 == 0){
            neighbor1 = newNeighbor;
            visited = true;
        }
        else if(neighbor2 == 0 && neighbor1->getIndex() != newNeighbor->getIndex()){
            neighbor2 = newNeighbor;
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
        oneCon2Hub = true;
        twoCon2Hub = true;
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

    void Node::changeNeigTo(Node& oldNeigh, Node& newNeigh){
        int oldNeighInd = getNeighborInd(oldNeigh);
        if( oldNeighInd != 0){
            changeNeighbor(oldNeighInd, &newNeigh);
        }
    }

    bool Node::hasNeighbor(Node& posNeighbor){
        if (neighbor1 == 0){
            return false;
        }
        if (neighbor2 == 0){
            return neighbor1->getIndex() == posNeighbor.getIndex(); 
        }

        return neighbor1->getIndex() == posNeighbor.getIndex() || neighbor2->getIndex() == posNeighbor.getIndex();
    }

    bool Node::isVisited(){
        return visited;
    }

    float Node::calcTotDistance(){
        if (neighbor2 != 0){
            return calcDistance(*neighbor1) + calcDistance(*neighbor2);
        }
        else if (neighbor1 != 0){
            return calcDistance(*neighbor1);
        }
        else{
            return 0;
        }
        
    }

