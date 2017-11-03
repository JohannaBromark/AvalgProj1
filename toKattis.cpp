#include <iostream>
#include <math.h>
#include <tuple>
#include <vector>
#include <tuple>
#include <algorithm>
#include "Node.h"

using namespace std;

void greedy(vector<Node>& towns){
    int minDistance = -1;
    int distance; 
    int currentBestIndex;
    
    for(int i = 0; i < towns.size()-1; i++){
        minDistance = -1;
        for (int j = i+1; j < towns.size(); j++){
            distance = round(towns[i].calcDistance(towns[j]));
            if (minDistance < 0 || distance < minDistance){
                currentBestIndex = j;
                //cout << "best index " << j << endl;
                minDistance = distance;
            }
        }
        //cout << "ändrar i listan" << endl;
        Node moveForward = towns[currentBestIndex];
        Node moveBackward = towns[i+1];
        
        //cout << "flyttar nod " << moveForward.getIndex() << "Till pos: " << i+1 << endl;
        //cout << "flyttar nod " << moveBackward.getIndex() << "Till pos: " << currentBestIndex << endl;

        towns[i+1] = moveForward;
        towns[currentBestIndex] = moveBackward;   
    }
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

int main(){
    cout << "Hello, World! :)" << endl;
    int numTowns;
    cin >> numTowns;
    float afloat = 1.6;
    int aint = round(afloat);

    //cout << "float: " << afloat << "int: " << aint << endl;

    //int numTowns = std::stoi(getline(input));
    float inputString;
    float inputString2;
    vector<Node> towns;

    for(int n = 0; n<(numTowns); n++){
        cin >> inputString;
        cin >> inputString2;
        towns.push_back(Node(inputString, inputString2, n));
    }
    greedy(towns);
/*
    for (int i = 0; i<numTowns; i++){
        cout << towns[i].getIndex() << endl;
    }
*/
    vector<Node> newTour= new2Opt(towns);

    //cout << "-----------------------"<<endl;

    for (int i = 0; i<numTowns; i++){
        cout << newTour[i].getIndex() << endl;
    }
}



