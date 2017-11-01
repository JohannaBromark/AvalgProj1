// 2-opt local search 

#ifndef _TwoOpt_h
#define _TwoOpt_h

#include <vector>
#include "Node.h"
class Node;

extern int neighDist; //every translation unit that includes the header knows about this

class TwoOpt {
public:
    TwoOpt(std::vector<Node&>& cities);

private:
    int numCities;

    std::vector<Node&>& cities;
    
    int trySwap();

};

#endif //_TwoOpt_h
