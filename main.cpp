//Här kommenterar Johanna
//Här kommenterar Johanna igen

#include <iostream>
#include <math.h>
#include <tuple>

class City {
    float x, y;
    int index;

    public:
        float calcDistance (City&);
        City(float inX, float inY, int inIndex){
            x = inX; y = inY; index = inIndex;
        }
        std::tuple<float, float> getXY(){
            return std::make_tuple(x, y);
        };

};


float City::calcDistance (City& otherCity){
    std::tuple<float, float> otherXY = otherCity.getXY();
    return sqrt(pow( ( x - otherXY.get(0) ), 2 )+pow( ( y - otherXY.get(1) ), 2 ));
};


int main() {
    std::cout << "Hello, World! :)" << std::endl;
    return 0;
}
