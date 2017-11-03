#include <iostream>
#include <math.h>
#include <tuple>
#include <vector>
#include <tuple>
#include "new2Opt.h"
#include "Christofides.h"

//noderna ligger i en lista i den ordning de ska skrivas ut. 2opt ändrar i listan

using namespace std;

int mod(int num, int denum){
    if (num >= 0){
        return num%denum;
    }
    else{
        return (denum >= 0 ? denum : -denum) -1 + (num+1)%denum;
    }
}

vector<Node> changeTour(int city1, int city2, vector<Node> *tour){
    
    vector<Node> newVector;
    //cout << "längd på tour i början inne i swap: " << tour.size() << endl
    //cout << "Ska byta "<< city1 << "och" << city2;
    
    for (int start = 0; start < city1; start++){
        //cout << "Lägger in först: " << tour[c].getIndex() << endl;
        newVector.push_back((*tour)[start]);
    }

    for(int inv = 0; inv <= city2-city1; inv ++){
        //cout << "Lägger in omvänt: " << tour[city2 - num].getIndex() << endl;
        newVector.push_back((*tour)[city2 - inv]);
    }

    for (int end = city2+1; end < (*tour).size(); end ++){
        //cout << "Lägger in sist: " << tour[end].getIndex() << endl;
        newVector.push_back((*tour)[end]);
    }
    return newVector;
}

void new2Opt(vector<Node>& cityVector){
    int newDistance;
    int currentDistance;
    int numCities = cityVector.size();
    //cout << "antalet noder in: " << numCities;
    //cout << "längd på tour i början: " << currentTour.size();
    bool find = true;

    while (find){
        find = false;
        for (int city1 = 0; city1 < numCities; city1++){
            for (int city2 = city1+1; city2 < numCities-1; city2++){
                
                currentDistance = cityVector[mod(city1-1, numCities)].calcDistance(cityVector[mod(city1, numCities)]) + 
                cityVector[mod(city2, numCities)].calcDistance(cityVector[mod(city2+1, numCities)]);
                
                newDistance = cityVector[mod(city1-1, numCities)].calcDistance(cityVector[mod(city2, numCities)]) + 
                cityVector[mod(city1, numCities)].calcDistance(cityVector[mod(city2+1, numCities)]);
                
                //cout << "längden på touren: " << newTour.size();
                //cout << "avstånd innan: " << bestDistance << " avstånd efter: " << newDistance << endl;
                
                if (newDistance < currentDistance){
                    cityVector = changeTour(city1, city2, &cityVector);
                    find = true;
                }
            }
        }
    }
}

vector<Node> changeTour2H(int city1, int city2, vector<Node> *tour){
    vector<Node> newVector;
    
    for (int start = 0; start < city1; start++){
        newVector.push_back((*tour)[start]);
    }

    for(int skip = city1+1; skip <= city2; skip ++){
        
        newVector.push_back((*tour)[skip]);
    }
    newVector.push_back((*tour)[city1]);

    for (int end = city2+1; end < (*tour).size(); end ++){
        newVector.push_back((*tour)[end]);
    }
    return newVector;
}

void new2HOpt(vector<Node>& cityVector){
    int currentDistance;
    int newDistance;
    
    int numCities = cityVector.size();
    //cout << "antalet noder in: " << numCities;
    //cout << "längd på tour i början: " << currentTour.size();
    bool find = true;

    while (find){
        find = false;
        for (int city1 = 0; city1 < numCities; city1++){
            for (int city2 = city1+2; city2 < numCities-1; city2++){
                
                currentDistance = cityVector[mod(city1-1, numCities)].calcDistance(cityVector[mod(city1, numCities)]) +
                cityVector[mod(city1, numCities)].calcDistance(cityVector[mod(city1+1, numCities)])+ 
                cityVector[mod(city2, numCities)].calcDistance(cityVector[mod(city2+1, numCities)]);
                
                newDistance = cityVector[mod(city1-1, numCities)].calcDistance(cityVector[mod(city1+1, numCities)]) +
                cityVector[mod(city2, numCities)].calcDistance(cityVector[mod(city1, numCities)])+ 
                cityVector[mod(city1, numCities)].calcDistance(cityVector[mod(city2+1, numCities)]);
                
                //cout << "längden på touren: " << newTour.size();
                //cout << "avstånd innan: " << bestDistance << " avstånd efter: " << newDistance << endl;
                
                if (newDistance < currentDistance){
                    cityVector = changeTour2H(city1, city2, &cityVector);
                    find = true;
                }
            }
        }
    }
}