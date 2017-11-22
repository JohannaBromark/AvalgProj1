#include <iostream>
#include <math.h>
#include <vector>
//#include <ctime>
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


vector<Town> changeTour(int city1, int city2, int city3, vector<Town> *tour){
    
    vector<Town> newVector;
    //cout << "längd på tour i början inne i swap: " << tour.size() << endl
    //cout << "Ska byta "<< city1 << "och" << city2;
    


    // från start til och med x1
    for (int start = 0; start <= city1; start++){
        newVector.push_back((*tour)[start]);
    }

    // hopp från x1 till x2+1

    // från och med x2 +1 till och med x3
    for(int inv = city2+1; inv <= city2+1-city3; inv ++){
        newVector.push_back((*tour)[city2+1 + inv]);
    }

    // hopp från x3 till x2

    // från och med x2 till och med x1 +1 (baklänges originalvägen)
    for(int inv = 0; inv <= city2-city1+1; inv ++){
        newVector.push_back((*tour)[city2 - inv]);
    }

    // hopp x1 +1 till x3 +1

    // från och med x3+1 till och med x1
    for (int end = city3+1; end < (*tour).size(); end ++){
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


void threeOpt(vector<Town>& cityVector){
    int newDistance;
    int currentDistance;
    int numCities = cityVector.size();
    bool find = true;

    while (find){
        find = false;
        for (int city1 = 0; city1 < numCities; city1++){
            for (int city2 = city1+1; city2 < numCities-1; city2++){
                for(int city3 = city2+1; city3 < numCities-2; city3++){
                    
                    currentDistance = cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)]) + cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]) + cityVector[mod(city3, numCities)].calcDistance(&cityVector[mod(city3+1, numCities)]);

                    newDistance =  cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]) + cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city3, numCities)]) + cityVector[mod(city3+1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)]);
                    
                
                    if (newDistance < currentDistance){
                        cityVector = changeTour(city1, city2, city3, &cityVector);
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

            threeOpt(towns);



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


}
