#include <iostream>
//#include <math.h>
//#include <tuple>
//#include "Node.h"
#include <vector>
//#include <tuple>
//#include <algorithm>
//#include "clarkeWright.h"
//#include "LinKernighan.h"
//#include "Savings.h"
//#include <string>
#include "Christofides.h"

using namespace std;
/*
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


float calcTour2(vector<Node>& nodes) {
    float dist = 0.0;
    for (int i = 0; i < nodes.size() - 1; i++) {
        dist += nodes.at(i).calcDistance(nodes.at(i+1));
    }
    dist += nodes.at(0).calcDistance(nodes.at(nodes.size()-1));
    return dist;
}*/
int main(){

    int numTowns;
    cin >> numTowns;
    
    //int numTowns = std::stoi(getline(input));
    long double inputString;
    long double inputString2;
    vector<Vertix> towns;

    for(int n = 0; n<(numTowns); n++){
        cin >> inputString;
        cin >> inputString2;
        //cout << inputString << " "<< inputString2 <<" " << n << endl;
        towns.push_back(Vertix(inputString, inputString2, n));
    }
/*
    
    Node stad1(2.3, 4.3, 0);
    Node stad2(1.0, 2.4, 1);
    Node stad3(1.5, 5.4, 2);
    Node stad4(3.6, 3.5, 3);
    Node stad5(1.5, 7.4, 3);
*/
    //greedy(towns, towns[0]);
    //clarkeWright(towns);
    //printTour(towns);
    //cout << calcTour(towns) << endl;

    Christofides testChristofides = Christofides(towns);
    /*vector<Node> townsInOrder;
    townsInOrder.push_back(towns.at(0));
    townsInOrder.push_back(towns.at(8));
    townsInOrder.push_back(towns.at(4));
    townsInOrder.push_back(towns.at(9));
    townsInOrder.push_back(towns.at(2));
    townsInOrder.push_back(towns.at(6));
    townsInOrder.push_back(towns.at(1));
    townsInOrder.push_back(towns.at(7));
    cout << calcTour2(townsInOrder)<< endl;*/


    return 0;
}
