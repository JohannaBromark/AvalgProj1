//
// Created by Isabelle Hallman on 2017-10-30.
//

#include "LinKernighan.h"
#include <iostream>

LinKernighan::LinKernighan(std::vector<Node>& citiesIn) : cities(citiesIn){
    std::cout << "Påbörjar..." << cities.size() << std::endl;
    generateInitial();
    std::cout << "Längd " << initialTour.size() << std::endl;
    std::vector<Edge> newTour = initialTour;
    long currentDistance = calcTourDistance();
    G = 0;

    int i = 0;

    Edge x1 = initialTour.at(0);
    setOfX.emplace_back(x1);
    Node& fromT = x1.getNode(1);
    int nextT = 3;
    std::cout << "Påbörjar..." << std::endl;

    //Step 4
    while (nextT < cities.size()) {
        float g = x1.getDistance() - fromT.calcDistance(cities.at(nextT));
        if (g > 0) {
            setOfY.emplace_back( Edge(fromT, cities.at(nextT)) );
            G += g;
            newTour.at(0) = setOfY.at(0);
            break;
        };
        nextT++;
    }
    std::cout << "Påbörjar nu..." << std::endl;

    if (setOfY.size() == 0) {
        //start over, new first edge
        std::cout << "hej" << std::endl;

    }


    while (true) { //Lägg in schysst brytning
        //Step 5

        i ++;
        //Step 6
        fromT = setOfY.at(i-1).getNode(1);
        std::cout << "Påbörjar...3" << std::endl;

        int edgeIndex = 0;
        for (Edge possibleEdge : initialTour) {
            std::cout << "Påbörjar...3" << std::endl;

            if ( possibleEdge.getNode(0) == fromT || possibleEdge.getNode(1) == fromT) {
                if ( checkIfTour( Edge( ((possibleEdge.getNode(0) ==  fromT)
                                         ? possibleEdge.getNode(1) : possibleEdge.getNode(0)),
                                        cities.at(0)), edgeIndex)
                     && !checkIfRepeated(possibleEdge, 1, i)) {
                    setOfX.emplace_back(possibleEdge);
                }
                edgeIndex++;
            }
        }

        //Step 7

        break;
    }
}



void LinKernighan::generateInitial() {
    //Generates initial tour in order of 0, 1, 2....
    for (int i = 0; i < cities.size() - 1; i++) {
        initialTour.emplace_back( Edge( cities.at(i), cities.at(i+1) ) );
    }
    //Close the tour
    initialTour.emplace_back( Edge( cities.at(cities.size() - 1), cities.at(0) ) );
}

bool LinKernighan::checkIfTour(Edge newEdge, int index) {
    return true;
}

long LinKernighan::calcTourDistance() {
    long distance = 0;
    for (Edge e : initialTour) {
        distance += e.getDistance();
    }
    return distance;
}

bool LinKernighan::checkIfRepeated(Edge newEdge, int setToCheck, int index) {
    //0 = setOfX, 1 = setOfY
    if (setToCheck == 0) {
        int loopIndex = 0;
        for (Edge xEdge : setOfX){
            if (xEdge == newEdge) {
                return true;
            }
            if (loopIndex > index) {
                break;
            }
        }
    }
    else {
        int loopIndex = 0;
        for (Edge yEdge : setOfY){
            if (yEdge == newEdge) {
                return true;
            }
            if (loopIndex >= index) {
                break;
            }
        }
    }
    return false;
}

void LinKernighan::printTour(std::vector<Edge>& tourToPrint) {
    int index = tourToPrint.at(0).getNode(0).getIndex();
    for (int i = 1; i < tourToPrint.size(); i++) {
        index = (index == tourToPrint.at(i).getNode(0).getIndex())
                ? tourToPrint.at(i).getNode(1).getIndex() : tourToPrint.at(i).getNode(0).getIndex();
        std::cout << index;
    }
    std::cout << std::endl;
}