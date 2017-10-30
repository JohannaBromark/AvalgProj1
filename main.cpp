//14:02

#include <iostream>
#include <math.h>
#include <tuple>
#include "node.h"

class City {
    float x, y;
    int index;

    public:
        City (float xIn, float yIn, int indexIn) {
            x = xIn; y = yIn; index = indexIn;
        }

        std::tuple<float, float> getXY() {
            return std::make_tuple(x, y);
        };

        float calcDistance (City& otherCity) {
                return sqrt(pow( ( x - std::get<0>(otherCity.getXY()) ), 2 ) + pow( ( y - std::get<1>(otherCity.getXY()) ), 2 ));
            };
};

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

int main() {
    std::cout << "Hello, World! :)" << std::endl;
    return 0;
}
