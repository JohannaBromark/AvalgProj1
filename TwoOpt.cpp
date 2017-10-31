// 2-opt local search 

#include <cstdlib>
// #include <ctime>
#include <math.h>
#include "TwoOpt.h"

TwoOpt::TwoOpt(std::vector<Node&>& citiesIn) : cities(citiesIn){
    int neighDist = 10; // only the CPP file creates this.
    int numCities = citiesIn.size();

}

void TwoOpt::trySwap(){
    // srand (time(0)); // initialize random seed
    int nodeInd = rand() %  numCities + 1; // generate number between 1 and numCities
    int dist = rand() %  neighDist + 1; // generate number between 1 and neighDist


    // First edge is choosen at random
    Node* node1 = cities.at(nodeInd);
    Node* node2 = *node1.getNeighbor(2);


    // Next edge is found by jumping dist forward
    Node** node3 = *node2.getNeighbor(2);
    Node** prev = *node2;
    for(int a=1; a<dist; a=a+1) {
        prev = node3;        
        if(node3.getNeighbor(2) != prev){
            node3 = *node3.getNeighbor(2);
        } else {
            node3 = *node3.getNeighbor(1);
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

        int node2Neigh = node2.getNeighborInd(node1);
        if( node2Neigh != 0){
            node2.changeNeigbor(node2Neigh, node4);
        }

        int node3Neigh = node3.getNeighborInd(node4);
        if( node3Neigh != 0){
            node3.changeNeigbor(node3Neigh, node1);
        }

        int node4Neigh = node4.getNeighborInd(node3);
        if( node4Neigh != 0){
            node4.changeNeigbor(node4Neigh, node2);
        }


    }
    
    

}
