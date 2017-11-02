// 2-opt local search 

/// NOT WORKING!

#include <cstdlib>
#include <iostream>
// #include <ctime>
#include <math.h>
#include "TwoOpt.h"

using namespace std;

void twoOpt(std::vector<Node> &nodes){
    int const neighDist = 10; // only the CPP file creates this.
    trySwap(nodes);
    

}

int trySwap(std::vector<Node> &nodesIn){
    int numNodes = nodesIn.size();
    // srand (time(0)); // initialize random seed
    int nodeInd = rand() %  numNodes + 1; // generate number between 1 and numNodes
    int dist = rand() %  neighDist + 1; // generate number between 1 and neighDist


    // First edge is choosen at random  
    Node& node1 = nodesIn.at(nodeInd);  // node1 is a pointer that points at a pointer
    Node& node2 = node1.getNeighbor(2); // node2 is a pointer that points at a pointer


    // Next edge is found by jumping dist forward
    node3 = &node2.getNeighbor(2);
    int prev = node2.getIndex(); // prev is the value at the address that is pointed to by the pointer node 2


    for(int a=1; a<dist; a=a+1) {
        prev = *node3; // if prev is equal to the value at the adress that is pointed to by node3
        if(node3.getNeighbor(2).getIndex() != prev){
            node3 = &node3.getNeighbor(2); // node 3 is now the pointer that points at the address where a node that has a neigbor is
        } else {
            node3 = &node3.getNeighbor(1); // node 3 is now the pointer that points at the address where a node that has a neigbor is
        }
        cout << node3.getIndex() << endl;
    }

    // Edge from node3 to node4 is not to "go back"
    if(node3.getNeighbor(2).getIndex() != prev){
        node4 = &node3.getNeighbor(2); // node4 is a pointer that points at a pointer
    } else {
        node4 = &node3.getNeighbor(1); // node4 is a pointer that points at a pointer
    }


    // calculate distances
    // get the value from the adresses that are pointed to by node1-4
    float ogDist = *node1.calcDistance(node2) + *node3.calcDistance(node4);
    float newDist = *node1.calcDistance(node3) + *node2.calcDistance(node4);
    
    // if the new way is shorter, swap egdes
    if(newDist < ogDist){

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
        // HEEEEEEEEEEEEEEEEEEEELLLLLLLLLLLLLLLLLLLLLLPPPPPPPPPPPPPPPPpp
        // I want to change the objects that gets pointed to by node1-4
        // HUUUUUUUUUUUUUUR?
        node1.changeNeigbor(2, node3);
        
        node2.changeNeigTo(node1, node4);
        node3.changeNeigTo(node4, node1);
        node4.changeNeigTo(node3, node2);
        
        // swap was made successfully
        return 1;
    }
    
    // no swap was made
    return 0;

}
