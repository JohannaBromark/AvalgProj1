#include <iostream>
#include <math.h>
#include <vector>
//#include <time.h>
#include <ctime>
#include <algorithm>
#include <limits>
#include "Christofides.h"

using namespace std;
/*
struct Town {
    double x, y;
    int index;

    Town(double xIn, double yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
    }

    int calcDistance(Town *other) {
        return (int) sqrt(pow( ( x - (*other).getX() ), 2 ) + pow( ( y - (*other).getY() ), 2 ));
    }

    double getX(){
        return x;
    }

    double getY(){
        return y;
    }
};
*/
void greedy(vector<Town>& towns){
    int minDistance = -1;
    int distance; 
    int currentBestIndex;
    
    for(int i = 0; i < towns.size()-1; i++){
        minDistance = -1;
        for (int j = i+1; j < towns.size(); j++){
            distance = round(towns[i].calcDistance(&towns[j]));
            if (minDistance < 0 || distance < minDistance){
                currentBestIndex = j;
                //cout << "best index " << j << endl;
                minDistance = distance;
            }
        }
        //cout << "ändrar i listan" << endl;
        Town moveForward = towns[currentBestIndex];
        Town moveBackward = towns[i+1];
        
        //cout << "flyttar nod " << moveForward.getIndex() << "Till pos: " << i+1 << endl;
        //cout << "flyttar nod " << moveBackward.getIndex() << "Till pos: " << currentBestIndex << endl;

        towns[i+1] = moveForward;
        towns[currentBestIndex] = moveBackward;   
    }
}

vector<Town> changeTour(int city1, int city2, vector<Town> *tour){
    
    vector<Town> newVector;
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

int calcTourDist(vector<Town>& tour){
    int totalDist = 0;
    for (int i = 0; i < tour.size()-1; i++){
        totalDist += tour[i].calcDistance(&tour[i+1]);
    }
    totalDist += tour[tour.size()-1].calcDistance(&tour[0]);
    return totalDist;
}

int mod(int num, int denum){
    if (num >= 0){
        return num%denum;
    }
    else{
        return (denum >= 0 ? denum : -denum) -1 + (num+1)%denum;
    }
}

vector<Town> changeTour2H(int city1, int city2, vector<Town> *tour){
    vector<Town> newVector;
    
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


void new2Opt(vector<Town>& cityVector){
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
                
                currentDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1, numCities)]) + 
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);
                
                newDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city2, numCities)]) + 
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);
                
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

void new2HOpt(vector<Town>& cityVector){
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
                
                currentDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1, numCities)]) +
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)])+ 
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);
                
                newDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)]) +
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city1, numCities)])+ 
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);
                
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

void randomOpt(vector<Town> &cityVector){
    int numCities = (cityVector).size();
    int city1;
    int city2;
    int city3;
    int city4;
    int currentTourDistance;
    int newTourDistance;
    int numLoops = 2;
    vector<Town> newTour;

    while (numLoops > 0){
        city1 = rand() % numCities;
        city2 = rand() % (numCities-city1) +city1;
        city3 = rand() % numCities;
        city4 = rand() % (numCities-city3) +city3;
             
        newTour = changeTour(city1, city2, &cityVector);
        newTour = changeTour(city3, city4, &newTour);
        new2Opt(newTour);
        new2HOpt(newTour);
        newTourDistance = calcTourDist(newTour);
        currentTourDistance = calcTourDist(newTour);
        if (newTourDistance < currentTourDistance){
            cityVector = newTour;
        }

        numLoops --;
    }
}

int main(){

    //cout << "Done!" << endl;

    srand(time(NULL));
    int numTowns;
    cin >> numTowns;
    
    double inputString;
    double inputString2;
    vector<Town> towns;

    for(int n = 0; n<(numTowns); n++){
        cin >> inputString;
        cin >> inputString2;
        towns.push_back(Town(inputString, inputString2, n));
    }
    vector<Town> bestRoute;
    int currentBestDist = std::numeric_limits<int>::max();
    std::srand ( unsigned ( std::time(0) ) );

    if (numTowns > 1) {
        for (int i = 0; i < 4; i++) {
            greedy(towns);

            new2Opt(towns);
            new2HOpt(towns);
            //new2Opt(towns);
            //new2HOpt(towns);

            //randomOpt(towns);
            int thisTourDist = calcTourDist(towns);
            if (thisTourDist < currentBestDist) {
                bestRoute = towns;
                currentBestDist = thisTourDist;
                //cout << "Changed bestRoute" << endl;
            }
            std::random_shuffle(towns.begin(), towns.end());
        }
        for (Town ver : bestRoute) {
            cout << ver.index << endl;
        }

    }
    else {
        cout << 0 << endl;
    }

}

