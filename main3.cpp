#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
#include "clarkeWright.h"

using namespace std;



int calcTourDist(vector<Node>& tour){
    int totalDist = 0;
    for (int i = 0; i < tour.size()-1; i++){
        totalDist += tour[i].calcDistance(tour[i+1]);
    }
    totalDist += tour[tour.size()-1].calcDistance(tour[0]);
    return totalDist;
}

int main(){
    
        //cout << "Done!" << endl;
    
        //srand(time(NULL));
        int numTowns;
        cin >> numTowns;
        
        double inputString;
        double inputString2;
        vector<Node> towns;
    
        for(int n = 0; n<(numTowns); n++){
            cin >> inputString;
            cin >> inputString2;
            towns.push_back(Node(inputString, inputString2, n));
        }
        vector<Node> bestRoute;
    
        if (numTowns > 1) {
            chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
            clarkeWright(towns);
            //new2Opt(towns); 
            //new2HOpt(towns);

            chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
                
                int routeLenght = calcTourDist(towns);
                auto totTime = chrono::duration_cast<chrono::microseconds>(end - start).count(); 
                
            cout << "Ruttlängd: " << routeLenght <<endl;
            cout << "Tid [ms]: " <<totTime << endl;
            return 0;
        }
        return 0;
}
    