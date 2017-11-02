#include "clarkeWright.h"
#include <iostream>
#include <algorithm>

class Savings;
class Node;

using namespace std;

bool sortOrder(const Savings& save1, const Savings& save2){
    return save2.getSave() < save1.getSave();
}

vector<Savings> calcSavings(vector<Node>& cityVector){
    //Works!!

    //vector<tuple<float, Node&, Node&>> savingVector;
    vector<Savings> savingVector;
    int numCities = cityVector.size();
    Node& hub = cityVector[0];
    
    //Error control
    if (numCities ==0){
        return savingVector;
    }
    if (numCities <= 2){
        //tuple<float, Node&, Node&> specTuple1 (0, hub, hub);
        savingVector.push_back(Savings(hub, hub, cityVector[numCities-1]));
        return savingVector;
    } 

    //Loop over all cites and calcs the distance between them. Does not include the hub.
    for (int city1 = 1; city1 < numCities; city1++){
        for (int city2 = city1+1; city2 < numCities; city2++){
            Node& node1 = cityVector[city1];
            Node& node2 = cityVector[city2];
            savingVector.push_back(Savings(hub, node1, node2));
        }
    }
    
    return savingVector;
}

void connectNodes(Node& conNode1, Node& conNode2, int& counter){
    //Only connects two nodes if one of them is only connected to the hub. This prevents sub cycles. 
    cout << conNode1.getIndex() << endl;
    cout << conNode2.getIndex() << endl;

    if ((conNode1.isOnlyConnectedToHub() && conNode2.isConnectedToHub()) || (conNode2.isOnlyConnectedToHub()&& conNode1.isConnectedToHub())){
        conNode1.addNeighborCW(&conNode2);
        conNode2.addNeighborCW(&conNode1);
        counter-= 2;
    }
}

void addNodesToHub(std::vector<Node>& citiesVector){
    //Works!!
    Node &theHub = citiesVector[0];
    //adding the hub to itself as well
    for (int n = 0; n<citiesVector.size(); n++){
        citiesVector[n].connectToHub(&theHub);
    }
}


void clarkeWright(vector<Node>& cities){
    //Seems to work!!

    //The first city in the vector is the hub.
    addNodesToHub(cities);
    
    vector<Savings> savings = calcSavings(cities);
    
    sort(savings.begin(), savings.end(), [](const Savings& save1, const Savings& save2){ return save2.getSave() < save1.getSave(); });
    
    cout << savings[0].getSave() << endl;
    cout << get<0>(savings[0].getNodes()).getIndex() << endl;
    cout << get<1>(savings[0].getNodes()).getIndex() << endl;
    cout << savings[1].getSave() << endl;
    cout << get<0>(savings[1].getNodes()).getIndex() << endl;
    cout << get<1>(savings[1].getNodes()).getIndex() << endl;
   
    //Counter for # connectsion the hub has. Must be at least 2. Initially two per city
    
    int numHubConnections = (cities.size()-1)*2;
    int& refNumHub = numHubConnections;
    //Looping over the savings, which are in an non-increasing order
    cout << "antalet sparanden " << savings.size(); 
    
    for (int i = 0; i<savings.size(); i++){
        // When the hub only has two connections left, we're done. 
        //cout << "antalet kopplingar till hubben: " << numHubConnections;
        if (numHubConnections == 2){
            cout << "breaks: " << endl;
            break;
        }        
        //pop_heap(savings.begin(), savings.end(), sortOrder);        
        
        //Checks if it is OK that the nodes can be connected and connects them. 
        connectNodes(get<0>(savings[i].getNodes()), get<1>(savings[i].getNodes()), refNumHub);
    }

    for (int k = 1; k < cities.size(); k++){
        if (cities[k].isConnectedToHub()){
            //cout << "Hittade en nod med index: " << cities[k].getIndex() << endl;
            cities[0].addNeighborCW(&cities[k]);
        }
    }

}
