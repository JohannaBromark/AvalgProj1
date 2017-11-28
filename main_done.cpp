#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

/*
Authors:
Jacob Björkman, jacobbj@kth.se
Johanna Bromark, bromark@kth.se
Isabelle Hallman, ihal@kth.se
*/

using namespace std;

struct Town {
    //Structure to for the cities
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
    //Greedy algorithm for finding an "optimal" tour by chosing the the city that is closest. 
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
    // Changes position of two cities and putting the cities in the middle in reverse order. 
    vector<Town> newVector;    
    for (int start = 0; start < city1; start++){
        newVector.push_back((*tour)[start]);
    }

    for(int inv = 0; inv <= city2-city1; inv ++){
        newVector.push_back((*tour)[city2 - inv]);
    }

    for (int end = city2+1; end < (*tour).size(); end ++){
        newVector.push_back((*tour)[end]);
    }
    return newVector;
}

int calcTourDist(vector<Town>& tour){
    //Computes the total distance of the tour
    int totalDist = 0;
    for (int i = 0; i < tour.size()-1; i++){
        totalDist += tour[i].calcDistance(&tour[i+1]);
    }
    totalDist += tour[tour.size()-1].calcDistance(&tour[0]);
    return totalDist;
}

int mod(int num, int denum){
    // Customized modolu function that handles the negative values
    if (num >= 0){
        return num%denum;
    }
    else{
        return (denum >= 0 ? denum : -denum) -1 + (num+1)%denum;
    }
}

vector<Town> changeTour2H(int city1, int city2, vector<Town> *tour){
    // Similar to changeTour, but places city1 in between of city2 and city2 + 1. Used in 2.5Opt
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
    // Similar to changeTour, but places city2 in between of city1-1 and city1. Used in 2.5Opt
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

void new2Opt(vector<Town>& cityVector){
    //Implemented 2-opt that serches for edges that can be changed to get at shorter route. 
    int newDistance;
    int currentDistance;
    int numCities = cityVector.size();
    bool find = true;

    while (find){
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
    }
}

void new2HOpt(vector<Town>& cityVector){
    //Implemented 2.5-opt that serches for cities that can be moved in between of other edges. 
    int currentDistance;
    int newDistance;
    int currentDistance2;
    int newDistance2;
    
    int numCities = cityVector.size();
    bool find = true;

    while (find){
        find = false;
        for (int city1 = 0; city1 < numCities; city1++){
            for (int city2 = city1+2; city2 < numCities-1; city2++){
                
                
                // Is A-B-C and C-D or A-C and C-B-D a better choice 
                currentDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1, numCities)]) +
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)])+ 
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);
                
                newDistance = cityVector[mod(city1-1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)]) +
                cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city1, numCities)])+ 
                cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]);

                // Is A-B and C-D-E or A-D-B and C-E a better choice 
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

    if (numTowns > 1) {

        for (int i = 0; i < 2; i++) {
            greedy(towns);
            new2Opt(towns);
            new2HOpt(towns);

            int thisTourDist = calcTourDist(towns);
            if (thisTourDist < currentBestDist) {
                bestRoute = towns;
                currentBestDist = thisTourDist;
            }
        }
        
        for (Town ver : bestRoute) {
            cout << ver.index << endl;
        }
    }
    else {
        cout << 0 << endl;
    }

    return 0;
}
