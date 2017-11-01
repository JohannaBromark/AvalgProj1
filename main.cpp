#include <iostream>
#include <math.h>
#include <tuple>
#include "Node.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include "LinKernighan.h"
#include "Savings.h"

using namespace std;

bool sortOrder(Savings& save1, Savings& save2){
    return save2.getSave() < save1.getSave();
}

/*
bool sortOrder(const tuple<float, Node, Node>& tuple1, const tuple<float, Node, Node>& tuple2){
    //Works!!
    float f1 = get<0>(tuple1);
    float f2 = get<0>(tuple2);
    
    return f2 < f1;
}
*/
vector<tuple<float, Node&, Node&>> calcSavings(vector<Node>& cityVector){
    //Works!!

    vector<tuple<float, Node&, Node&>> savingVector;
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

void connectNodes(Node& conNode1, Node& conNode2, int& counter){
    //Only connects two nodes if one of them is only connected to the hub. This prevents sub cycles. 
    if (conNode1.isOnlyConnectedToHub() || conNode2.isOnlyConnectedToHub()){
        conNode1.addNeighbor(&conNode2);
        conNode2.addNeighbor(&conNode1);
        counter--;
    }
}

void addNodesToHub(vector<Node>& citiesVector){
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
    
    vector<tuple<float, Node&, Node&>> savings = calcSavings(cities);
    
    cout << "Efter savings" << endl;
    cout << cities.at(1).getIndex() << endl;
    cout << cities[2].getIndex() << endl;
    cout << cities[3].getIndex() << endl;
    //sort(savings.begin(), savings.end(), sortOrder);
    cout << "Efter sort" << endl;
    cout << cities.at(1).getIndex() << endl;
    cout << cities[2].getIndex() << endl;
    cout << cities[3].getIndex() << endl;
    //Counter for # connectsion the hub has. Must be at least 2. Initially two per city
    int numHubConnections = (cities.size()-1)*2;
    int& refNumHub = numHubConnections;
    //Looping over the savings, which are in an non-increasing order
        
    for (int i = 0; i<savings.size(); i++){
        // When the hub only has two connections left, we're done. 
        if (numHubConnections == 2){
            cout << "breaks: " << endl;
            break;
        }
        

        //tuple<float, Node&, Node&> save = savings.front();
        
        //pop_heap(savings.begin(), savings.end(), sortOrder);        
        
        tuple<float, Node&, Node&>& save = savings[i];
        //Retreives the two nodes that makes the save 
        Node& node1 = get<1>(save);
        Node& node2 = get<2>(save);
        
        //Checks if it is OK that the nodes can be connected and connects them. 
        connectNodes(node1, node2, refNumHub);

    }
    for (int k = 1; k < cities.size(); k++){
        cout << k << endl;
        cout << cities.at(1).getIndex() << endl;
        cout << cities[2].getIndex() << endl;
        cout << cities[3].getIndex() << endl;

        if (cities[k].isConnectedToHub()){
            cout << "Hittade en nod med intex: " << cities[k].getIndex() << endl;
            cities[0].addNeighbor(&cities[k]);
        }
    }
}

int main() {
    cout << "Hello, World! :)" << endl;
    Node stad1(2.3, 4.3, 0);
    Node stad2(1.0, 2.4, 1);
    Node stad3(1.5, 5.4, 2);
<<<<<<< HEAD
    Node stad4(3.6, 3.5, 3);
=======
    Node stad4(1.5, 7.4, 3);
>>>>>>> a507c028107dd695e2c2ff766b63fcf6cf58ebbf

    cout << stad1.getIndex() << endl;
    cout << stad2.getIndex() << endl;

    vector<Node> citiesTest = {stad1, stad2, stad3, stad4};

    if(!(citiesTest[1].getNeighbor(1) == 0)){
        cout << "Detta borde vara -1 " << citiesTest[1].getNeighbor(1)->getIndex() << endl;
    }
    
    cout << "I mainen innan hubconnection" << endl;
    cout << citiesTest.at(1).getIndex() << endl;
    cout << citiesTest[2].getIndex() << endl;
    cout << citiesTest[3].getIndex() << endl;
    
    Savings save(stad1, stad2, stad3);
    Savings save2(stad1, stad2, stad4);
    Savings save3(stad1, stad3, stad4);
    cout << "Save: " << save.getSave()<< endl;
    cout << "Save2: " << save2.getSave() <<endl;

    vector<Savings> saveVector = {save, save2, save3};

    sort(saveVector.begin(), saveVector.end(), sortOrder);

    cout << "Efter sortering";
    //cout << saveVector[0].getSave() << endl;
    //cout << saveVector[1].getSave() << endl;

    //tuple<Node&, Node&> tupleSave = save.getNodes();
    /* 
    cout << "Node1: " << get<0>(save.getNodes()).getIndex() << endl;
    cout << "Node2: " << get<1>(save.getNodes()).getIndex() << endl;
    cout << "Node1: " << get<0>(save2.getNodes()).getIndex() << endl;
    cout << "Node2: " << get<1>(save2.getNodes()).getIndex() << endl;    
    */


    /*
    addNodesToHub(citiesTest);
    //cout << "Detta borde vara 0" << citiesTest[1].getNeighbor(1)->getIndex() << endl;
    cout << "I mainen efter hubconnection" << endl;
    cout << citiesTest.at(1).getIndex() << endl;
    cout << citiesTest[2].getIndex() << endl;
    cout << citiesTest[3].getIndex() << endl;
    clarkeWright(citiesTest);
    cout << "Vad är detta nu? " << citiesTest[1].getNeighbor(1)->getIndex() << endl;
    cout << "Detta borde vara? " << citiesTest[1].getNeighbor(2)->getIndex() << endl;
    cout << "Vad är detta nu? " << citiesTest[2].getNeighbor(1)->getIndex() << endl;
    cout << "Detta borde vara? " << citiesTest[2].getNeighbor(2)->getIndex() << endl;
    cout << "hubbens kopplingar " << citiesTest[0].getNeighbor(1)->getIndex() << endl;
    cout << "hubbens kopplingar " << citiesTest[0].getNeighbor(2)->getIndex() << endl;
    */
    /*
    std::vector<Node> cities2;


    cout << "hejhejhej" <<endl;
    cities2.emplace_back(Node(1.0, 1.0, 0));
    cities2.emplace_back(Node(4.0, 4.0, 1));
    cities2.emplace_back(Node(10.0, 5.0, 2));
    cities2.emplace_back(Node(3.0, 4.0, 3));
    LinKernighan lin = LinKernighan(cities2);

    return 0;
    */
}
