// 2-opt local search 

#include <cstdlib>
// #include <ctime>
#include <math.h>
#include "TwoOpt.h"

TwoOpt::TwoOpt(std::vector<Node>& citiesIn) : cities(citiesIn){
    int neighDist = 10; // only the CPP file creates this.
    int numCities = citiesIn.size();
    TwoOpt::generateInitial();

}

void TwoOpt::generateInitial() {
    for (int i = 0; i < cities.size() - 1; i++) {
        setOfEdges.emplace_back( Edge( cities.at(i), cities.at(i+1) ) );
    }

    
    //Close the tour
    setOfEdges.emplace_back( Edge( cities.at(cities.size() ), cities.at(0) ) );
}

void TwoOpt::trySwap(){
    // srand (time(0)); // initialize random seed
    int edgeInd = rand() %  numCities + 1; // generate number between 1 and numCities
    int dist = rand() %  neighDist + 1; // generate number between 1 and neighDist

    Edge& Edge1 = setOfEdges.at(edgeInd);
    Edge& Edge2 = setOfEdges.at(edgeInd + dist);
    Node& Node1 = Edge1.getToNode();
    Node& Node2 = Edge1.getFromNode();
    Node& Node3 = Edge2.getToNode();
    Node& Node4 = Edge2.getFromNode();

    int ogDist = Edge1.getDistance() + Edge2.getDistance(); 
    int newDist = Node1.calcDistance(Node3) + Node2.calcDistance(Node4);
    
    if( newDist < ogDist){
        Edge newEdge = Edge(Node1, Node3);
        Edge newEdge2 = Edge(Node2, Node4);


    }
    
    

}
