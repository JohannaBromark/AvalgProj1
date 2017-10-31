// 2-opt local search 

#ifndef _TwoOpt_h
#define _TwoOpt_h

#include <vector>
#include "Edge.h"
class Node;

extern int neighDist; //every translation unit that includes the header knows about this

class TwoOpt {
public:
    TwoOpt(std::vector<Node>& cities);

private:
    int numCities;

    float G;
    std::vector<Node>& cities;
    std::vector<Edge> setOfEdges;
    

    bool checkIfTour(std::vector<Edge> tour);

    void generateInitial();

    void trySwap();

};

#endif //_TwoOpt_h
