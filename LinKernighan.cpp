//
// Created by Isabelle Hallman on 2017-10-30.
//

#include "LinKernighan.h"
#include <iostream>

LinKernighan::LinKernighan(std::vector<Node>& citiesIn) : cities(citiesIn){

    std::cout << "Påbörjar..." << cities.size() << std::endl;
    Edge test = Edge(cities.at(0), cities.at(1));
    std::cout << "Test " << test.getNode(1).getIndex() << ", " << cities.at(0).getIndex() << std::endl;

    generateInitial();
    std::cout << "Längd " << initialTour.size() << std::endl;
    std::vector<Edge> newTour = initialTour;
    printTour(initialTour);
    long currentTourDistance = calcTourDistance(initialTour);
    G = 0;
    int i = 0;
    bool yFound = false;
    int startIndex = 0;

    while (! yFound && startIndex < cities.size()) {
        yFound = findStartXY(startIndex);
        startIndex++;
        std::cout << "Hit." << cities.size() << std::endl;
        while (yFound) {
            std::cout << "Hit också." << cities.size() << std::endl;

            //Step 5
            i ++;
            //Step 6
            Node& fromT = setOfY.at(i-1).getNode(1);

            int edgeIndex = 0;
            for (Edge possibleEdge : initialTour) {

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

            if (calcTourDistance(newTour) < currentTourDistance) {
                currentTourDistance = calcTourDistance(newTour);
                startIndex = 0;
                initialTour = newTour;
                yFound = false;
                i = 0;
                break;
            }

            std::cout << "Och Hit." << cities.size() << std::endl;

            //Step 7

        }
    }
}


bool LinKernighan::findStartXY(int startIndex) {
    Edge& x1 = initialTour.at(startIndex);
    Node &fromT = x1.getNode(1);
    int nextT = 0;

    //Step 4
    while (nextT < cities.size()) {

        float g = x1.getDistance() - fromT.calcDistance(cities.at(nextT));
        std::cout << "...." << g << " for " << fromT.getIndex() << " & " << cities.at(nextT).getIndex() << std::endl;

        if (g > 0) {
            setOfY.emplace_back(Edge(fromT, cities.at(nextT)));
            setOfX.emplace_back(x1);
            G += g;
            newTour.at(startIndex) = setOfY.at(0);
            std::cout << "Hittade." << cities.size() << std::endl;

            return true;
        };
        nextT++;
    }
    std::cout << "Hithjkhljk." << cities.size() << std::endl;

    return false;
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

long LinKernighan::calcTourDistance(std::vector<Edge>& tour) {
    long distance = 0;
    for (Edge e : tour) {
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
    std::cout << index;
    for (int i = 1; i < tourToPrint.size(); i++) {
        index = (index == tourToPrint.at(i).getNode(0).getIndex())
                ? tourToPrint.at(i).getNode(1).getIndex() : tourToPrint.at(i).getNode(0).getIndex();
        std::cout << " " << index;
    }
    std::cout << std::endl;
}