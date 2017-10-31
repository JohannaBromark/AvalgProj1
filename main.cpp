//14:02

#include <iostream>
#include <math.h>
#include <tuple>
#include "Node.h"
#include "LinKernighan.h"

using namespace std;

/*
class Savings {
    float value;
    City& cityBase, city1, city2; //Referenser för att spara plats (?)

public:
    Savings (City& cityBaseIn, City& city1In, City& city2In)
        : cityBase(cityBaseIn), city1(city1In), city2(city2In) //Referenserna måste skapas direkt, görs på detta sätt
    {
        value = cityBase.calcDistance(city1) + city2.calcDistance(cityBase) - city2.calcDistance(city1);
    }

    float getValue (){
        return value;
    }

    bool operator<(Savings& other) {      //Implements < comparator
        return value < other.getValue();
    }
    bool operator>(Savings& other) { //Implements > comparator
        return value > other.getValue();
    }
};
*/
int main() {
    cout << "Hello, World! :)" << endl;
    Node stad1(2.3, 4.3, 0);
    cout << stad1.getIndex() << endl;

    std::vector<Node> cities2;
    cities2.emplace_back(Node(1.0, 1.0, 0));
    cities2.emplace_back(Node(4.0, 4.0, 1));
    cities2.emplace_back(Node(3.0, 3.0, 2));
    LinKernighan lin = LinKernighan(cities2);

}
