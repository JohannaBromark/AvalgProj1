// 2-opt local search 

/// NOT WORKING!

#include <cstdlib>
#include <iostream>
//#include <algorithm>
//#include <random>
//#include <chrono>
//#include <time.h>
//#include <ctime>
#include <math.h>
#include "TwoOpt.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>        /* time */



using namespace std;

void twoOpt(std::vector<Node> &nodes){
    srand (time(NULL));
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
    //cout << "ts1"<< endl;
    int const neighDist = (nodesIn.size())/2; // only the CPP file creates this.
        
    int numNodes = nodesIn.size();
    // initialize random seed
    
    int dist;
    int nodeInd;
    nodeInd = rand() %  numNodes; // generate number between 1 and numNodes
    dist = rand() %  neighDist + 1; // generate number between 1 and neighDist

    cout <<"Dist: "<< dist << " Nodeind: "<<nodeInd<< endl;

    //cout << "ts2"<< endl;
   
    // First edge is choosen at random  
    int node1 = nodeInd;  // node1 is a pointer that points at a pointer
    int node2 = nodesIn[node1].getNeighbor(2)->getIndex(); // node2 is a pointer that points at a pointer


    int node3;
    // Next edge is found by jumping dist forward
    cout << "neigh1: " << nodesIn[node2].getNeighbor(1)->getIndex() << endl;
    cout << "neigh2: " << nodesIn[node2].getNeighbor(2)->getIndex() << endl;
    cout << "node1: " << node1 << endl;



    if(nodesIn[node2].getNeighbor(2)->getIndex() != node1){
        node3 = nodesIn[node2].getNeighbor(2)->getIndex();
    } else{
        node3 = nodesIn[node2].getNeighbor(1)->getIndex();
    }
    cout << "node3: " << node3 << endl;

    
    int prev = node2; // prev is the value at the address that is pointed to by the pointer node 2
    int prevPrev = node2;

    //cout << "ts3"<< endl;
    

    for(int a=0; a < dist; a++) {
        if(nodesIn[node3].getNeighbor(2)->getIndex() != prev && nodesIn[node3].getNeighbor(2)->getIndex() != prevPrev){
            node3 = nodesIn[node3].getNeighbor(2)->getIndex(); // node 3 is now the pointer that points at the address where a node that has a neigbor is
        } else if (nodesIn[node3].getNeighbor(1)->getIndex() != prev && nodesIn[node3].getNeighbor(1)->getIndex() != prevPrev ){
            node3 = nodesIn[node3].getNeighbor(1)->getIndex(); // node 3 is now the pointer that points at the address where a node that has a neigbor is
        } else {
            cout << "ERRRRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR" << endl;
            return 0;
        }
        prevPrev = prev;
        prev = node3; // if prev is equal to the value at the adress that is pointed to by node3
        
    }    
    //cout << "ts4"<< endl;
    
    int node4;
    // Edge from node3 to node4 is not to "go back"
    if(nodesIn[node3].getNeighbor(2)->getIndex() != prev && nodesIn[node3].getNeighbor(2)->getIndex() != prevPrev){
        node4 = nodesIn[node3].getNeighbor(2)->getIndex(); // node4 is a pointer that points at a pointer
    } else {
        node4 = nodesIn[node3].getNeighbor(1)->getIndex(); // node4 is a pointer that points at a pointer
    }
    //cout << "ts5"<< endl;
    cout << "####Node3 var: " << node3 << "Node4 var: " << node4 << endl;
    


    // calculate distances
    // get the value from the adresses that are pointed to by node1-4

    cout << "Nodes: " << node1 <<" "<< node2 <<" "<< node3 <<" "<< node4 << endl;

    float ogDist = nodesIn[node1].calcDistance(nodesIn[node2]) +  nodesIn[node3].calcDistance(nodesIn[node4]);
    float newDist = nodesIn[node1].calcDistance(nodesIn[node3]) + nodesIn[node2].calcDistance(nodesIn[node4]);
    
    
    // if the new way is shorter, swap egdes
    if(newDist < ogDist){        
        nodesIn[node1].changeNeigTo(nodesIn[node2], nodesIn[node3]);
        nodesIn[node2].changeNeigTo(nodesIn[node1], nodesIn[node4]);
        nodesIn[node3].changeNeigTo(nodesIn[node4], nodesIn[node1]);
        nodesIn[node4].changeNeigTo(nodesIn[node3], nodesIn[node2]);
        
        // swap was made successfully
        return 1;
        
    }
    
    // no swap was made
    return 0;

}
