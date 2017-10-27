//Här kommenterar Johanna
//Här kommenterar Johanna igen

#include <iostream>
#include <math.h>

float calcDistance(float x1, float y1, float x2, float y2){
    return sqrt(pow((x1-x2), 2)+pow((y1-y2), 2));
}


class City {
    public:
        float calcDistance (City);
};


float City::calcDistance (City& otherCity){

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
