//Här kommenterar Johanna
//Här kommenterar Johanna igen

#include <iostream>
#include <math.h>
#include <tuple>

class City {
    float x, y;
    int index;

    public:
        City(float inX, float inY, int inIndex){
            x = inX; y = inY; index = inIndex;
        }

        float calcDistance (City& otherCity) {
            return sqrt(pow( ( x - std::get<0>(otherCity.getXY()) ), 2 ) + pow( ( y - std::get<1>(otherCity.getXY()) ), 2 ));
        };

        std::tuple<float, float> getXY(){
            return std::make_tuple(x, y);
        };

};

int main() {
    std::cout << "Hello, World! :)" << std::endl;
    return 0;
}
