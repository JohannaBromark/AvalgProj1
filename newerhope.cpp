#include <iostream>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <limits>
#include <list>

using namespace std;

struct Town {
    double x, y;
    int index;

    Town(double xIn, double yIn, int indexIn) {
        x = xIn; y = yIn; index = indexIn;
    }

    int calcDistance(Town &other) {
        return round(sqrt(pow( ( x - (other).getX() ), 2 ) + pow( ( y - (other).getY() ), 2 )));
    }

    double getX(){
        return x;
    }

    double getY(){
        return y;
    }
};

void greedy(list<Town> &towns){  // fixed for list
    int minDistance;
    int distance; 

    std::list<Town>::iterator it;
    for (it = towns.begin(); it != prev(towns.end()); it++){
        //cout << "it: yx" << it->getY() << it->getX() << endl;
        
        //cout << "next(it): yx" << next(it)->getY() << next(it)->getX() << endl;
        //cout << "it: yx" << it->getY() << it->getX() << endl;


        minDistance = it->calcDistance(*next(it));
        cout << "mindistance" << minDistance << endl;
        std::list<Town>::iterator it2;
        for (it2 = towns.begin(); it2 != towns.end(); ++it2){
            if(it != it2){
               distance = it->calcDistance(*it2);
               cout << "distance" << distance << endl;
               if (distance < minDistance){
                   cout << "swapping!" << endl;
                   std::swap(*next(it) , *it2);
               }
            }
        }
    }
}

int calcTourDist(list<Town>& tour){ // fixed for list
    int totalDist = 0;
    
    for (auto town = tour.begin(); town != tour.end(); ++town){
         totalDist += town->calcDistance(*(next(town,1)));
    }

    totalDist += tour.back().calcDistance((tour.front()));
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


list<Town> changeTour(list<Town>::iterator city1, list<Town>::iterator city2, list<Town> &tour){    
    list<Town> newList;


    tour.splice(tour.begin(), tour, city1, city2);

    return tour;










    /*
    for (int start = 0; start < city1; start++){
        newList.push_back((*tour)[start]);
    }

    for(int inv = 0; inv <= city2-city1; inv ++){
        //cout << "Lägger in omvänt: " << tour[city2 - num].getIndex() << endl;
        newList.push_back((*tour)[city2 - inv]);
    }

    for (int end = city2+1; end < (*tour).size(); end ++){
        //cout << "Lägger in sist: " << tour[end].getIndex() << endl;
        newList.push_back((*tour)[end]);
    }
    */
    //return newList;
}



/*
vector<Town> changeTour2H(int city1, int city2, vector<Town> *tour){
    vector<Town> newList;
    
    for (int start = 0; start < city1; start++){
        newList.push_back((*tour)[start]);
    }

    for(int skip = city1+1; skip <= city2; skip ++){
        
        newList.push_back((*tour)[skip]);
    }
    newList.push_back((*tour)[city1]);

    for (int end = city2+1; end < (*tour).size(); end ++){
        newList.push_back((*tour)[end]);
    }
    return newList;
}

vector<Town> changeTour2H2(int city1, int city2, vector<Town> *tour){
    vector<Town> newList;
    
    for (int start = 0; start < city1; start++){
        newList.push_back((*tour)[start]);
    }

    newList.push_back((*tour)[city2]);

    for(int cont = city1; cont < city2; cont ++){ 
        newList.push_back((*tour)[cont]);
    }

    for (int end = city2+1; end < (*tour).size(); end ++){
        newList.push_back((*tour)[end]);
    }
    return newList;
}




void new2Opt(vector<Town>& cityVector, time_t timeBudget, time_t startTime){
    time_t timeElapsed = difftime(time(NULL), startTime);


    int newDistance;
    int currentDistance;
    int numCities = cityVector.size();
    //cout << "antalet noder in: " << numCities;
    //cout << "längd på tour i början: " << currentTour.size();
    bool find = true;

    while (find && timeElapsed < timeBudget){
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
    //cout << "antalet noder in: " << numCities;
    //cout << "längd på tour i början: " << currentTour.size();
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
                
                //cout << "längden på touren: " << newTour.size();
                //cout << "avstånd innan: " << bestDistance << " avstånd efter: " << newDistance << endl;
                
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
*/
int main(){
    int numTowns;
    cin >> numTowns;
    
    double inputString;
    double inputString2;
    list<Town> towns;

    for(int n = 0; n<(numTowns); n++){
        cin >> inputString;
        cin >> inputString2;
        towns.push_back(Town(inputString, inputString2, n));
    }
    list<Town> bestRoute;
    int currentBestDist = std::numeric_limits<int>::max();

    time_t endwait;
    time_t start = time(NULL);
    double timeBudget = 1.95; // stop randomizing when this has passed
    srand(start);


    int thisTourDist;
    double timeElapsed = 0.0;

    int amLoop = 0; // keep track of loops

    if (numTowns > 1) {
        for (Town ver : towns) {
            cout << ver.index << endl;
        }



        greedy(towns);
        list<Town>::iterator it1 = towns.begin();
        list<Town>::iterator it2 = towns.begin();
        //advance(it2, 3);
        cout << "towns size: "<< towns.size() << endl;
        
        
        towns = changeTour(it1, it2, towns);
        
        while  (timeElapsed < timeBudget) {
            amLoop ++;

            //cout << "yey" << endl;

            //new2Opt(towns, timeBudget, start);
            
            if(timeElapsed >= timeBudget){
                break;
                //cout << "BREAK!" << endl;                

            }
            //new2HOpt(towns, timeBudget, start);


            thisTourDist = calcTourDist(towns);
            if (thisTourDist < currentBestDist) {
                bestRoute = towns;
                currentBestDist = thisTourDist;
            }
            
            //std::random_shuffle(towns.begin(), towns.end());
            timeElapsed = difftime(time(NULL), start);
        }
        //for (Town ver : bestRoute) {
        cout << "lol" << endl;
        cout << "towns size: "<< towns.size() << endl;
        for (Town ver : towns) {
            cout << ver.index << endl;
        }

    }
    else {
        cout << 0 << endl;
    }










    cout << "Elapsed time: " << timeElapsed << endl;
    cout << "Loops: " << amLoop << endl;

    //return 0;

}

