//node.h

#ifndef _Node_h   //    if node.h hasn't been included yet...
#define _Node_h   //    #define this so the compiler knows it has been included
#include <tuple>
#include <math.h>

class Node { 

    public:
        Node(float x, float y, int index);
        float calcDistance (Node& otherCity);        
        std::tuple<float, float> getXY();
        bool operator==(Node& other);		
        int getIndex();
    private:
        float x, y;
        int index;
        Node& neighbor1;
        Node& neighbor2;
};

#endif //_Node_h