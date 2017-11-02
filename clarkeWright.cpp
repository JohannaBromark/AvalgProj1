#include "clarkeWright.h"
#include <iostream>
#include <algorithm>

class Savings;
class Node;

using namespace std;

bool sortOrder(const Savings& save1, const Savings& save2){
    return save2.getSave() < save1.getSave();
}

/*
bool sortOrder(const tuple<float, Node, Node>& tuple1, const tuple<float, Node, Node>& tuple2){
    //Works!!
    float f1 = get<0>(tuple1);
    float f2 = get<0>(tuple2);
    
    return f2 < f1;
}*/

/*
vector<tuple<float, Node&, Node&>> calcSavings(vector<Node>& cityVector){
    //Works!!

    std::vector<tuple<float, Node&, Node&>> savingVector;
    int numCities = cityVector.size();
    Node& hub = cityVector[0];
    //Error control
    if (numCities == 1){
        tuple<float, Node&, Node&> specTuple1 (0, hub, hub);
        savingVector.push_back(specTuple1);
    }
    //Error control
    if (numCities == 2){
        tuple<float, Node&, Node&> specTuple2 (0, hub, cityVector[1]);
        savingVector.push_back(specTuple2);
        return savingVector;
    }   

    //Loop over all cites and calcs the distance between them. Does not include the hub.
    for (int city1 = 1; city1 < numCities; city1++){
        for (int city2 = city1+1; city2 < numCities; city2++){
            Node& node1 = cityVector[city1];
            Node& node2 = cityVector[city2];
            float saving = hub.calcDistance(node1)+hub.calcDistance(node2) - node1.calcDistance(node2);
            tuple<float, Node&, Node&> aSaving(saving, node1, node2);
            savingVector.push_back(aSaving);
        }
    }

    cout << "Efter loop i SAvings" << endl;
    cout << cityVector.at(1).getIndex() << endl;
    cout << cityVector[2].getIndex() << endl;
    cout << cityVector[3].getIndex() << endl;

    //Make heap byter ut alla index till två????
    //make_heap(savingVector.begin(), savingVector.end(), sortOrder);
    //sort(savingVector.begin(), savingVector.end(), sortOrder);
    cout << "Efter heapen" << endl;
    cout << cityVector.at(1).getIndex() << endl;
    cout << cityVector[2].getIndex() << endl;
    cout << cityVector[3].getIndex() << endl;
    return savingVector;
}
*/
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
     
    cout << "Nod 1 bara kopplad till hubben " << conNode1.isOnlyConnectedToHub() << endl;
    cout << "Nod 2 bara kopplad till hubben " << conNode2.isOnlyConnectedToHub()<< endl;
    cout << "Nod 1 kopplad till huppen " << conNode1.isConnectedToHub()<< endl;
    cout << "Nod 2 kopplad till hubben " << conNode2.isConnectedToHub()<< endl;
    if ((conNode1.isOnlyConnectedToHub() && conNode2.isConnectedToHub()) || (conNode2.isOnlyConnectedToHub()&& conNode1.isConnectedToHub())){
        conNode1.addNeighborCW(&conNode2);
        conNode2.addNeighborCW(&conNode1);
        counter-= 2;
        cout << "Nod 1 bara kopplad till hubben efter " << conNode1.isOnlyConnectedToHub()<< endl;
        cout << "Nod 2 bara kopplad till hubben efter " << conNode2.isOnlyConnectedToHub()<< endl;
        cout << "Nod 1 kopplad till huppen efter " << conNode1.isConnectedToHub()<< endl;
        cout << "Nod 2 kopplad till hubben efter " << conNode2.isConnectedToHub()<< endl;
        cout << "------------------------------------"<< endl;

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
    cout << "Efter sort" << endl;
    cout << cities.at(1).getIndex() << endl;
    cout << cities[2].getIndex() << endl;
    cout << cities[3].getIndex() << endl;

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
