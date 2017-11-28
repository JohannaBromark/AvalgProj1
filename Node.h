//node.h

#ifndef _Node_h   //    if node.h hasn't been included yet...
#define _Node_h   //    #define this so the compiler knows it has been included
#include <tuple>
#include <math.h>

class Node { 

    public:
        Node(double x, double y, int index);
        int calcDistance (Node& otherCity);
        int getIndex();
        std::tuple<float, float> getXY();
        
        
        bool operator==(Node& other);		
        void addNeighbor(Node *newNeighbor);
        void addNeighborCW(Node *newNeighbor);
        bool isConnectedToHub();
        bool isOnlyConnectedToHub();
        void connectToHub(Node *hubNode);
        Node* getNeighbor(int neighborNum);
        void changeNeighbor(int neighborN, Node *aNewNeighbor);
        void changeNeigTo(Node& oldNeigh, Node& newNeigh);
        int getNeighborInd(Node& neighbor);
        bool hasNeighbor(Node& posNeighbor);
        bool isVisited();
        float calcTotDistance();
        //void setIsVisited();
        

    private:
        float x, y;
        int index;
        
        Node *neighbor1;
        Node *neighbor2;
        bool oneCon2Hub;
        bool twoCon2Hub;
        //bool visited;
};

#endif //_Node_h