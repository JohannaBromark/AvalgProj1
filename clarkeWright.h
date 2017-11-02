#include "Node.h"
#include "Savings.h"
#include <vector>
#include <tuple>

using namespace std;

bool sortOrder(Savings& save1, Savings& save2);

vector<Savings> calcSavings(vector<Node>& cityVector);

void connectNodes(Node& conNode1, Node& conNode2, int& counter);

void addNodesToHub(vector<Node>& citiesVector);

void clarkeWright(vector<Node>& cities);
