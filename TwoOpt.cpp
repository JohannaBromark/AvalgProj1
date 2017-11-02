// 2-opt local search 

/// NOT WORKING!

#include <cstdlib>
#include <iostream>
// #include <ctime>
#include <math.h>
#include "TwoOpt.h"

using namespace std;

void twoOpt(std::vector<Node> &nodes){
    int noBetter = 0;
    /*
    if(trySwap(nodes)==0) {
        cout << "tryswap == 0" << endl;

    }else{
        cout << "tryswap == 1" << endl;
    }
    ;
    */
    while(noBetter<100){
        cout << "while!" << noBetter <<endl;
        if (trySwap(nodes)==0){
            cout << "tryswap == 0" << endl;            
            noBetter ++;
        }
        else{
            cout << "tryswap == 1" << endl;
        }
    }
    
    

}

int trySwap(std::vector<Node> &nodesIn){   
    int const neighDist = 10; // only the CPP file creates this.
        
    int numNodes = nodesIn.size();
    // srand (time(0)); // initialize random seed
    int nodeInd = rand() %  numNodes; // generate number between 1 and numNodes
    int dist = rand() %  neighDist + 1; // generate number between 1 and neighDist

   
    // First edge is choosen at random  
    int node1 = nodeInd;  // node1 is a pointer that points at a pointer
    int node2 = nodesIn[node1].getNeighbor(2)->getIndex(); // node2 is a pointer that points at a pointer


    // Next edge is found by jumping dist forward
    int node3 = nodesIn[node2].getNeighbor(2)->getIndex();
    int prev = nodesIn[node2].getIndex(); // prev is the value at the address that is pointed to by the pointer node 2


    for(int a=1; a<dist; a=a+1) {
        prev = node3; // if prev is equal to the value at the adress that is pointed to by node3
        if(nodesIn[node3].getNeighbor(2)->getIndex() != prev){
            node3 = nodesIn[node3].getNeighbor(2)->getIndex(); // node 3 is now the pointer that points at the address where a node that has a neigbor is
        } else {
            node3 = nodesIn[node3].getNeighbor(1)->getIndex(); // node 3 is now the pointer that points at the address where a node that has a neigbor is
        }
        
    }

    int node4;
    // Edge from node3 to node4 is not to "go back"
    if(nodesIn[node3].getNeighbor(2)->getIndex() != prev){
        node4 = nodesIn[node3].getNeighbor(2)->getIndex(); // node4 is a pointer that points at a pointer
    } else {
        node4 = nodesIn[node3].getNeighbor(1)->getIndex(); // node4 is a pointer that points at a pointer
    }


    // calculate distances
    // get the value from the adresses that are pointed to by node1-4
    float ogDist = nodesIn[node1].calcDistance(nodesIn[node2]) +  nodesIn[node3].calcDistance(nodesIn[node4]);
    float newDist = nodesIn[node1].calcDistance(nodesIn[node3]) + nodesIn[node2].calcDistance(nodesIn[node4]);
    
    // if the new way is shorter, swap egdes
    if(newDist < ogDist){

        nodesIn[node1].changeNeighbor(2, &nodesIn[node3]);
        
        nodesIn[node2].changeNeigTo(nodesIn[node1], nodesIn[node4]);
        nodesIn[node3].changeNeigTo(nodesIn[node4], nodesIn[node1]);
        nodesIn[node4].changeNeigTo(nodesIn[node3], nodesIn[node2]);
        
        // swap was made successfully
        return 1;
    }
    
    // no swap was made
    return 0;

}
