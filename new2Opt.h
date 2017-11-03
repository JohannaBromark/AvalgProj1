
#include <tuple>
#include <vector>
#include <tuple>
#include "Node.h"

using namespace std;

vector<Node> new2Opt(vector<Node>& cityVector);
vector<Node> swapEdges(int city1, int city2, vector<Node>& tour);
int calcTourDist(vector<Node>& tour);
