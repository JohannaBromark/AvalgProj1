//
// Created by Isabelle Hallman on 2017-11-01.
//

#include "Christofides.h"
#include <set>
#include <unordered_set>

int compareEdge(const void *s1, const void *s2) {
    struct EdgeK *e1 = (struct EdgeK *) s1;
    struct EdgeK *e2 = (struct EdgeK *) s2;
    return int(e1->weight - e2->weight);
}

Christofides::Christofides(std::vector<Node>& citiesIn) : cities(citiesIn), nodeSets(citiesIn.size()) {
    //std::cout << "Initerar" << std::endl;
    fullGraph.v = (int) cities.size();
    //std::cout << "initialsize "<<fullGraph.v;
    fullGraph.e = fullGraph.v * (fullGraph.v-1)/2;
    fullGraph.edges = new EdgeK[fullGraph.e];
    addEdges();
    struct EdgeK result[fullGraph.v - 1];
    kruskal(result);

    std::vector<std::list<int>> verticesAdjacency(cities.size());

    perfectMatching(result, verticesAdjacency);
    hierholzer(verticesAdjacency);
    printTour(eulerTour);
    std::cout << "\n"<< "\n" << std::endl;
    //Remove duplicates
    std::unordered_set<int> s;
    eulerTour.remove_if([&](int n) {
        return (s.find(n) == s.end()) ? (s.insert(n), false) : true;
    });
    //std::cout << "Klar!" << std::endl;
    printTour(eulerTour);
}

void Christofides::addEdges(){
    //std::cout << "AddEdges" << std::endl;

    int counter = 0;
    for (int i = 0; i < cities.size() - 1; i++){
        for (int j = i + 1; j < cities.size(); j++){
            fullGraph.edges[counter].from = i;
            fullGraph.edges[counter].to = j;
            fullGraph.edges[counter].weight = cities.at(i).calcDistance(cities.at(j));
            counter++;
        }
        counter++;
    }
}

void Christofides::kruskal(struct EdgeK result[]){
    //Create minimal spanning tree through Kruskal's algorithm
    //std::cout << "Kruskal" << std::endl;

    std::qsort(fullGraph.edges, fullGraph.e, sizeof(struct EdgeK), compareEdge);

    int i, n;
    for (i = n = 0; i < fullGraph.e && n < fullGraph.v - 1; i++) {
        int u = fullGraph.edges[i].from; int v = fullGraph.edges[i].to;
        if (nodeSets.findParent(u) != nodeSets.findParent(v)) {
            result[n] = fullGraph.edges[i];
            nodeSets.addDegree(u);
            nodeSets.addDegree(v);
            n++;
            nodeSets.unite(v, u);
        }
    }
    //std::cout << "Result at pos 3 " << result[3].from << std::endl;
}

void Christofides::perfectMatching(struct EdgeK edgesIn[], std::vector<std::list<int>>& verticesAdjacency) {
    //std::cout << "Perfect Matching" << std::endl;
    //Does not produce minimal perfect matching --> could be improved.

    std::vector<int> unevenVset = nodeSets.generateUnevenVset();
    int nUnevenV = unevenVset.size();

    int counter, i;
    int n = (int) nUnevenV * (nUnevenV - 1) / 2;

    struct EdgeK edges[n];
    for (counter = i = 0; i < nUnevenV-1; i++) {
        for (int j = i + 1; j < nUnevenV; j++) {
            edges[counter].from = unevenVset.at(i);
            edges[counter].to = unevenVset.at(j);
            edges[counter].weight = cities.at(edges[counter].from).calcDistance(cities.at(edges[counter].to));
            counter++;
        }
    }

    std::set<int> usedNodes;
    newGraph.v = fullGraph.v; newGraph.e = nUnevenV / 2 + fullGraph.v - 1;
    newGraph.edges = new EdgeK[newGraph.e];

    std::qsort(edges, n, sizeof(struct EdgeK), compareEdge);
    counter = 0;
    for (i = 0; (i < n) && (counter < nUnevenV/2); i++) {
        if ( (usedNodes.count(edges[i].from) == 0) && (usedNodes.count(edges[i].to) == 0) ){
            //std::cout << "counter is " << counter << " limit for counter " << nUnevenV/2 << std::endl;

            usedNodes.insert(edges[i].from);
            usedNodes.insert(edges[i].to);
            newGraph.edges[newGraph.e - 1 - counter] = edges[i];
            verticesAdjacency.at(edges[i].from).emplace_back(edges[i].to);
            verticesAdjacency.at(edges[i].to).emplace_back(edges[i].from);
            counter++;
        }
    }

    for (int e = 0; e < (fullGraph.v - 1); e++) {
        newGraph.edges[e] = edgesIn[e];
        verticesAdjacency.at(edgesIn[e].from).emplace_back(edgesIn[e].to);
        //std::cout << "Vertix " << edgesIn[e].from << " adjacent to: " << verticesAdjacency.at(edgesIn[e].from).front() << std::endl;
        verticesAdjacency.at(edgesIn[e].to).emplace_back(edgesIn[e].from);
    }

    //std::cout << "Vertices adjacency for 0 at end of perfect " << verticesAdjacency.at(0).front() << std::endl;

}

void Christofides::hierholzer(std::vector<std::list<int>> verticesAdjacency) {
   //std::cout << "Hierholzer with edges " << newGraph.e << std::endl;

    int start = 0;
    int usedEdges = 0;
    std::list<int>::iterator it;
    bool keepChecking = true;
    while ( keepChecking ) {
        int current = start;

        std::list<int> subTour;
        subTour.emplace_back(current);

        do {
            int next = verticesAdjacency.at(current).back();
            subTour.emplace_back(next);
            verticesAdjacency.at(current).pop_back();
            current = next;
            usedEdges++;
        } while (start != current);

        //Move iterator to desired poisition

        it = std::find(eulerTour.begin(), eulerTour.end(), 1);
        eulerTour.splice(it, subTour); //merge lists

        //Assign new start with unvisisted edges
        keepChecking = false;
        for (int subStart = 0; subStart < verticesAdjacency.size(); subStart++) {
            if (!verticesAdjacency.at(subStart).empty()) {
                start = subStart;
                keepChecking = true;
                break;
            }
        }
    }
    //std::cout << std::endl;
}

void Christofides::printTour(std::list<int> inList) {
    /*for (int i : inList) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    */
    std::cout << eulerTour.front();
    auto iter = eulerTour.begin();
    iter++;
    for(iter; iter != eulerTour.end(); iter++){
        std::cout << "\n" << *iter;
    }
}