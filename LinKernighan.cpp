//
// Created by Isabelle Hallman on 2017-10-30.
//

#include "LinKernighan.h"

LinKernighan::LinKernighan(std::vector<Node&> citiesIn) : cities(citiesIn){

    generateInitial();

    int i = 0;
    int t = 0;
}

void LinKernighan::generateInitial() {
    for (int i = 0; i < cities.size() - 1; i++) {
        setOfX.push_back( Edge( cities.at(i), cities.at(i+1) ) );
    }
    //Close the tour
    setOfX.push_back( Edge( cities.at(cities.size() ), cities.at(0) ) );
}
