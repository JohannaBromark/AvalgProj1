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

using namespace std;

void greedy(vector<Node>& towns, Node& currentNode){
    float minDistance = -1.0;
    float distance; 
    int closestNeighIndex = 0;
    //cout << "Current Node: " << currentNode.getIndex() << endl;
    for(int i = 0; i<towns.size(); i++){
        
        if (currentNode.getIndex() != towns[i].getIndex()){
            distance = currentNode.calcDistance(towns[i]);
            //cout << "räknar avstånd: " <<distance << endl;

            //cout << (distance<minDistance) << (minDistance <0.0) << endl;

            //cout << currentNode.hasNeighbor(towns[i])<<endl;
            //cout << towns[i].isVisited() <<endl;
            if ((distance<minDistance || minDistance<0) && !currentNode.hasNeighbor(towns[i]) && !towns[i].isVisited()){
                //cout << "ändrar avstånd" << endl;
                minDistance = distance; 
                closestNeighIndex = towns[i].getIndex();
            }
        }
    }
    currentNode.addNeighbor(&towns[closestNeighIndex]);
    towns[closestNeighIndex].addNeighbor(&currentNode);
    if (closestNeighIndex != 0){
        greedy(towns, towns[closestNeighIndex]);
    }
    else {
        currentNode.addNeighbor(&towns[0]);
        towns[0].addNeighbor(&currentNode);
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
    
    //int numTowns = std::stoi(getline(input));
    float inputString;
    float inputString2;
    vector<Node> towns;

    for(int n = 0; n<(numTowns); n++){
        cin >> inputString;
        cin >> inputString2;
        towns.push_back(Node(inputString, inputString2, n));
    }
    
    greedy(towns, towns[0]);
    printTour(towns);        
    twoOpt(towns);
    printTour(towns);    
}

/*
    
    Node stad1(2.3, 4.3, 0);
    Node stad2(1.0, 2.4, 1);
    Node stad3(1.5, 5.4, 2);
    Node stad4(3.6, 3.5, 3);
    Node stad5(1.5, 7.4, 3);
    
    //greedy(towns, towns[0]);
    clarkeWright(towns);
    printTour(towns);  
    cout << calcTour(towns) << endl; 

    return 0;
}
*/
