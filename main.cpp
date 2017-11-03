#include <iostream>
#include <math.h>
#include <vector>
#include "Christofides.h"
#include "new2Opt.h"

using namespace std;



int main(){
    int numNodes;
    cin >> numNodes;
    float afloat = 1.6;
    int aint = round(afloat);

    //cout << "float: " << afloat << "int: " << aint << endl;

    //int numNodes = std::stoi(getline(input));
    float inputString;
    float inputString2;
    vector<Vertix> Nodes;

    for(int n = 0; n<(numNodes); n++){
        cin >> inputString;
        cin >> inputString2;
        Nodes.push_back(Vertix(inputString, inputString2, n));
    }

    Christofides test = Christofides(Nodes);
    vector<Node> tour = test.citiesOut;
    
    if (tour.size() > 1) {
        new2Opt(tour);
        new2HOpt(tour);


    for (Node node : tour) {
        cout << node.getIndex() << endl;
    }
    }
}
