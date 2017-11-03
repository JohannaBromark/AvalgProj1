
#include <tuple>
#include <vector>
#include <tuple>
#include "Christofides.h"
#include "Node.h"

using namespace std;

void new2Opt(vector<Node>& cityVector);
vector<Node> changeTour(int city1, int city2, vector<Node>& tour);
vector<Node> changeTour2H(int city1, int city2, vector<Node> *tour);
void new2HOpt(vector<Node>& cityVector);
//int calcTourDist(vector<Node>& tour);
