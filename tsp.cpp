#include <iostream>
#include <math.h>
#include <vector>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

struct Town {
    double x, y;
    int index;

    Town(double xIn, double yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
    }

    int calcDistance(Town *other) {
        return round(sqrt(pow( ( x - (*other).getX() ), 2 ) + pow( ( y - (*other).getY() ), 2 )));
    }

    double getX(){
        return x;
    }

    double getY(){
        return y;
    }
};

void greedy(vector<Town>& towns){
    int minDistance;
    int distance; 
    int currentBestIndex;
    
    for(int i = 0; i < towns.size()-1; i++){
        minDistance = towns[i].calcDistance(&towns[i+1]);
        for (int j = i+2; j < towns.size(); j++){
            distance = towns[i].calcDistance(&towns[j]);
            if (distance < minDistance){
                minDistance = distance;
                iter_swap(towns.begin()+ i+1, towns.begin()+j);
            }
        }   
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

vector<Town> changeTour2H2(int city1, int city2, vector<Town> *tour){
    vector<Town> newVector;
    
    for (int start = 0; start < city1; start++){
        newVector.push_back((*tour)[start]);
    }

    newVector.push_back((*tour)[city2]);

    for(int cont = city1; cont < city2; cont ++){ 
        newVector.push_back((*tour)[cont]);
    }

    for (int end = city2+1; end < (*tour).size(); end ++){
        newVector.push_back((*tour)[end]);
    }
    return newVector;
}




void new2Opt(vector<Town>& cityVector, time_t timeBudget, time_t startTime){
    time_t timeElapsed = difftime(time(NULL), startTime);


    int newDistance;
    int currentDistance;
    int numCities = cityVector.size();
    bool find = true;

    while (find && timeElapsed < timeBudget){
        find = false;
        for (int city1 = 0; city1 < numCities; city1++){
            for (int city2 = city1+1; city2 < numCities-1; city2++){                
                currentDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1, numCities)]) + 
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);

                newDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city2, numCities)]) + 
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);

                if (newDistance < currentDistance){
                    cityVector = changeTour(city1, city2, &cityVector);
                    find = true;
                }
            }
        }
        timeElapsed = difftime(time(NULL), startTime);
    }
}

void new2HOpt(vector<Town>& cityVector, time_t timeBudget, time_t startTime ){
    time_t timeElapsed = difftime(time(NULL), startTime);    
    int currentDistance;
    int newDistance;
    int currentDistance2;
    int newDistance2;
    
    int numCities = cityVector.size();
    bool find = true;

    while (find && timeElapsed < timeBudget){
        find = false;
        for (int city1 = 0; city1 < numCities; city1++){
            for (int city2 = city1+2; city2 < numCities-1; city2++){

                
                currentDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1, numCities)]) +
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)])+ 
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);
                
                newDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)]) +
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city1, numCities)])+ 
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);

                currentDistance2 = cityVector[mod(city2-1, numCities)].calcDistance(&cityVector[mod(city2, numCities)]) +
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)])+ 
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city1-1, numCities)]);
                
                newDistance2 = cityVector[mod(city2-1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]) +
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2, numCities)])+ 
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city1-1, numCities)]);
                
                if (newDistance < currentDistance || newDistance2 < currentDistance2){
                    if (newDistance-currentDistance < newDistance2-currentDistance2){
                        cityVector = changeTour2H(city1, city2, &cityVector);
                        find = true;
                    }
                    
                
                    else{
                        cityVector = changeTour2H2(city1, city2, &cityVector);
                        find = true;
                    }
                }
            }
        }
        timeElapsed = difftime(time(NULL), startTime);        
    }
}

int main(){
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

    time_t endwait;
    time_t start = time(NULL);
    double timeBudget = 2; // stop randomizing when this has passed
    srand(start);


    int thisTourDist;
    double timeElapsed = 0.0;

    if (numTowns > 1) {
         
        while  (timeElapsed < timeBudget) {
            greedy(towns);    
            new2Opt(towns, timeBudget, start);
            
            if(timeElapsed >= timeBudget){
                thisTourDist = calcTourDist(towns);
                if (thisTourDist < currentBestDist) {
                    bestRoute = towns;
                    currentBestDist = thisTourDist;
                }                
                break;
            } 
            else{
                new2HOpt(towns, timeBudget, start);
                thisTourDist = calcTourDist(towns);
                if (thisTourDist < currentBestDist) {
                    bestRoute = towns;
                    currentBestDist = thisTourDist;
                }
                
                std::random_shuffle(towns.begin(), towns.end());
                timeElapsed = difftime(time(NULL), start);                

            }  

        }
        
        for (Town ver : bestRoute) {
            cout << ver.index << endl;
        }

    }
    else {
        cout << 0 << endl;
    }
}