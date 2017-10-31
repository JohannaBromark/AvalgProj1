//
// Created by Isabelle Hallman on 2017-10-30.
//

#include "LinKernighan.h"
#include <algorithm>
#include <iostream>

LinKernighan::LinKernighan(std::vector<Node>& citiesIn) : cities(citiesIn){
    generateInitial();

    std::cout << "Jag kom hit "<< std::endl;
    Edge e = setOfX.at(0);
    std::cout << e.getDistance() << " hej" << std::endl;

    e = setOfX.at(1);
    std::cout << e.getDistance() << " hejdå"<< std::endl;


    /*

    int i = 0;

    Edge x1 = *setOfX.at(0);
    Node& fromT = x1.getToNode();
    int nextT = 3;

    //Step 4
    while (nextT < cities.size()) {
        if (x1.getDistance() - fromT.calcDistance(cities.at(nextT)) > 0) {
            *(setOfX[1]) = Edge(fromT, cities.at(nextT));
            setOfY.emplace_back(setOfX.at(1));
            break;
        };
        nextT++;
    }

    while (true) { //Lägg in schysst brytning
        i ++;
        Node& fromT = (*setOfX.at(i)).getNode();
        int nextI = i;
        while (nextI < cities.size()) {
            nextI++;
            Edge possibleEdge = Edge(fromT, cities.at(nextI));
            if (checkIfTour( possibleEdge , i)) {
                bool ok = true;
                for (int checkY = 0; checkY < i; checkY++) {
                    if (possibleEdge == *setOfY.at(checkY)) {
                        ok = false;
                    }
                }
                if (ok) {
                    *(setOfX[i]) = possibleEdge;
                }
            };
        }
        break;
    }*/
}

void LinKernighan::generateInitial() {
    //Generates initial tour in order of 0, 1, 2....
    for (int i = 0; i < cities.size() - 1; i++) {
        setOfX.emplace_back( Edge( cities.at(i), cities.at(i+1) ) );
    }
    //Close the tour
    setOfX.emplace_back( Edge( cities.at(cities.size() - 1), cities.at(0) ) );
}

bool checkIfTour(Edge newEdge, int index) {
    return true;
}



