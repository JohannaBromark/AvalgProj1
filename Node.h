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
        void addNeighbor(int i);
        bool isConnectedToHub();
        void connectToHub(int hubIndex);
        int getNeighbourIndex(int neighborNum);

    private:
        float x, y;
        int index;
        int neighbor1;
        int neighbor2;
        bool connectedHub;
};

#endif //_Node_h