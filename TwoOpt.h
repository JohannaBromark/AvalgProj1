// 2-opt local search 

#ifndef _TwoOpt_h
#define _TwoOpt_h

#include <vector>
#include "Node.h"
class Node;

extern int neighDist; //every translation unit that includes the header knows about this

void twoOpt(std::vector<Node> &nodes);

int trySwap(std::vector<Node> &nodesIn);

#endif //_TwoOpt_h
