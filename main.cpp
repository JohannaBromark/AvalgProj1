//Här kommenterar Johanna
//Här kommenterar Johanna igen

#include <iostream>
#include <math.h>
#include <tuple>

float calcDistance(float x1, float y1, float x2, float y2){
    return sqrt(pow((x1-x2), 2)+pow((y1-y2), 2));
}


class City {
    float x, y;
    int index;

    public:
        float calcDistance (City&);
        void City(float inX, float inY, int inIndex){
            x = inX; y = inY; index = inIndex;
        }
        std::tuple<float, float> getXY(){
            return std::make_tuple(x, y);
        };

};


float City::calcDistance (City& otherCity){
    return 0.0;
};


int main() {
    std::cout << "Hello, World! :)" << std::endl;
    return 0;
}
