//14:02

#include <iostream>
#include <math.h>
#include <tuple>
#include "Node.h"

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
    std::cout << "Hello, World! :)" << std::endl;
    
    Node stad(2.3, 4.3, 0);

    return 0;
}
