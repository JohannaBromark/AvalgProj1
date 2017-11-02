#include <iostream>
#include <math.h>
#include <tuple>
#include <vector>
#include <tuple>
#include "Node.h"
#include "Savings.h"
#include "new2Opt.h"

//noderna ligger i en lista i den ordning de ska skrivas ut. 2opt ändrar i listan

using namespace std;

vector<Node> new2Opt(vector<Node>& cityVector){
    
    int numLoops = 0;
    int newDistance = -1;
    int bestDistance = calcTourDist(cityVector);
    int numCities = cityVector.size();
    vector<Node> newTour;
    vector<Node> currentTour = cityVector;
    //cout << "antalet noder in: " << numCities;
    //cout << "längd på tour i början: " << currentTour.size();

    while (numLoops < 50){
        for (int city1 = 0; city1 < numCities; city1++){
            for (int city2 = city1+1; city2 < numCities; city2 ++){
                
                newTour = swapEdges(city1, city2, currentTour);
                
                //cout << "längden på touren: " << newTour.size();
                newDistance = calcTourDist(newTour);

                //cout << "avstånd innan: " << bestDistance << " avstånd efter: " << newDistance << endl;
                
                if (newDistance < bestDistance || newDistance < 0){
                    //cout << "innne i iffen" << endl;
                    bestDistance = newDistance;
                    currentTour = newTour;
                    numLoops = 0;
                }
                numLoops++; 
            }
        }
    }
    return currentTour;
}

vector<Node> swapEdges(int city1, int city2, vector<Node>& tour){
    
    vector<Node> newVector;

    //cout << "längd på tour i början inne i swap: " << tour.size() << endl;

    //cout << "Ska byta "<< city1 << "och" << city2;

    for (int c = 0; c < city1;c++){
        //cout << "Lägger in först: " << tour[c].getIndex() << endl;
        newVector.push_back(tour[c]);
    }
    int num = 0;
    for(int inv = city1; inv <= city2; inv ++){
        //cout << "Lägger in omvänt: " << tour[city2 - num].getIndex() << endl;
        newVector.push_back(tour[city2 - num]);
        num++;
    }

    for (int end = city2+1; end < tour.size() ; end ++){
        //cout << "Lägger in sist: " << tour[end].getIndex() << endl;
        newVector.push_back(tour[end]);
    }
    return newVector;
}

int calcTourDist(vector<Node>& tour){
    int totalDist = 0;
    for (int i = 0; i < tour.size()-1; i++){
        totalDist += tour[i].calcDistance(tour[i+1]);
    }
    totalDist += tour[tour.size()-1].calcDistance(tour[0]);
    return totalDist;
}