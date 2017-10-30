//node.h

//Guard
#ifndef _Node_h   //    if node.h hasn't been included yet...
#define _Node_h   //    #define this so the compiler knows it has been included
#include <tuple>
#include <math.h>

//class Node;

class Node { 

    public:
        Node(float x, float y, int index);
        float calcDistance (Node& otherCity);
        std::tuple<float, float> getXY();
    private:
        float x, y;
        int index;
        Node* neighbor1; 
        Node* neighbor2;
};

#endif 