#include <iostream>
#include <math.h>
#include <vector>
#include "Christofides.h"
#include "new2Opt.h"

using namespace std;

int main(){
    int numTowns;
    cin >> numTowns;
    float afloat = 1.6;
    int aint = round(afloat);

    //cout << "float: " << afloat << "int: " << aint << endl;

    //int numTowns = std::stoi(getline(input));
    float inputString;
    float inputString2;
    vector<Vertix> towns;

    for(int n = 0; n<(numTowns); n++){
        cin >> inputString;
        cin >> inputString2;
        towns.push_back(Vertix(inputString, inputString2, n));
    }

    Christofides test = Christofides(towns);
    if (test.citiesOut.size() > 1) {
        vector<Node> finalTour = new2Opt(test.citiesOut);

    for (Node node : finalTour) {
        cout << node.getIndex() << endl;
    };
    }
}
