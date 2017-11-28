#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
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

vector<Town> changeTour3O(int city1, int city2, int city3, vector<Town> &tour){
    
    vector<Town> newVector;
    //cout << "längd på tour i början inne i swap: " << tour.size() << endl
    //cout << "Ska byta "<< city1 << "och" << city2;
    


    // från start til och med x1
    for (int start = 0; start <= city1; start++){
        newVector.push_back(tour[start]);
    }

    // hopp från x1 till x2+1

    // från och med x2 +1 till och med x3
    for(int cont = city2+1; cont <= city3; cont ++){
        newVector.push_back(tour[cont]);
    }

    // hopp från x3 till x2

    // från och med x2 till och med x1 +1 (baklänges originalvägen)
    for(int inv = 0; inv <= city2-(city1+1); inv ++){
        newVector.push_back(tour[city2 - inv]);
    }

    // hopp x1 +1 till x3 +1

    // från och med x3+1 till och med x1
    for (int end = city3+1; end < tour.size(); end ++){
        newVector.push_back(tour[end]);
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
void twoOpt(vector<Town>& cityVector){
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

void threeOpt(vector<Town>& cityVector){
    int newDistance;
    int currentDistance;
    int numCities = cityVector.size();
    bool find = true;
    bool change = false;
    int c1;
    int c2;
    int c3;

    while (find){
        find = false;
        [&]{
            for (int city1 = 0; city1 < numCities; city1++){
                for (int city2 = city1+1; city2 < numCities-1; city2++){
                    for(int city3 = city2+1; city3 < numCities-2; city3++){
                        
                        currentDistance = cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)]) + cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]) + cityVector[mod(city3, numCities)].calcDistance(&cityVector[mod(city3+1, numCities)]);

                        newDistance =  cityVector[mod(city1, numCities)].calcDistance(&cityVector[mod(city2+1, numCities)]) + cityVector[mod(city2, numCities)].calcDistance(&cityVector[mod(city3, numCities)]) + cityVector[mod(city3+1, numCities)].calcDistance(&cityVector[mod(city1+1, numCities)]);
                        
                    
                        if (newDistance < currentDistance){
                            c1 = city1;
                            c2 = city2;
                            c3 = city3;

                            change  = true;                        
                            find = true;
                            return;
                        }
                    }
                }

            }
        }();
        if(change){
            cityVector = changeTour3O(c1, c2, c3, cityVector);
            change = false;
        }
    }
}



int main(){
    time_t endwait;
    time_t start = time(NULL);
    time_t seconds = 10; // end loop after this time has elapsed

    endwait = start + seconds;    


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

        while (start < endwait) {

            greedy(towns);

            twoOpt(towns);
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
