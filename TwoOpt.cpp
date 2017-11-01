// 2-opt local search 

/// NOT WORKING!

#include <cstdlib>
// #include <ctime>
#include <math.h>
#include "TwoOpt.h"

TwoOpt::TwoOpt(std::vector<Node&> &nodesIn) : nodes(&nodesIn){
    int const neighDist = 10; // only the CPP file creates this.
    int numNodes = nodesIn.size();

}

int TwoOpt::trySwap(){
    // srand (time(0)); // initialize random seed
    int nodeInd = rand() %  numNodes + 1; // generate number between 1 and numNodes
    int dist = rand() %  neighDist + 1; // generate number between 1 and neighDist


    // First edge is choosen at random
    node1 = &nodes.at(nodeInd);  // node1 pekar på adresplatsen för pekaren 
    node2 = &node1.getNeighbor(2);


    // Next edge is found by jumping dist forward
    node3 = &node2.getNeighbor(2);
    Node** prev = *node2;
    for(int a=1; a<dist; a=a+1) {
        prev = node3;        
        if(node3.getNeighbor(2) != prev){
            node3 = &node3.getNeighbor(2);
        } else {
            node3 = &node3.getNeighbor(1);
        }
    }

    // Edge from node3 to node4 is not to "go back"
    if(node3.getNeighbor(2) != prev){
        Node& node4 = *node3.getNeighbor(2);
    } else {
        Node& node4 = *node3.getNeighbor(1);
    }


    // calculate distances
    int ogDist = node1.calcDistance(node2) + node3.calcDistance(node4);
    int newDist = node1.calcDistance(node3) + node2.calcDistance(node4);
    
    // if the new way is shorter, swap egdes
    if(newDist < ogDist){
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
