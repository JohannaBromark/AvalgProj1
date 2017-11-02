#include <iostream>
#include <math.h>
#include <tuple>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>
#include "Node.h"
#include "clarkeWright.h"
#include "LinKernighan.h"
#include "Savings.h"
#include "TwoOpt.h"
#include "new2Opt.h"

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

void printTour(vector<Node>& nodesToPrint){
    int prevIndex = 0;
    int indexToPrint = 0;
    int nextIndex;
    for (int k = 0; k< nodesToPrint.size(); k++){
        cout << nodesToPrint[indexToPrint].getIndex() << endl;
        if (nodesToPrint[indexToPrint].getNeighbor(1)->getIndex() != prevIndex){
            nextIndex = nodesToPrint[indexToPrint].getNeighbor(1)->getIndex();
        }
        else{
            nextIndex = nodesToPrint[indexToPrint].getNeighbor(2)->getIndex();
        }
        prevIndex = indexToPrint;
        indexToPrint = nextIndex;
    }
}

float calcTour(vector<Node>& nodeInRoute){
    float totTour = 0.0;
    for (int t = 0; t<nodeInRoute.size(); t++){
        totTour+= nodeInRoute[t].calcTotDistance();
    }
    return totTour/2;
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
