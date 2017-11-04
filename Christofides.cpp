//
// Created by Isabelle Hallman on 2017-11-01.
//

#include "Christofides.h"
#include <set>
#include <unordered_set>
#include <algorithm>
#include "hungarian.h"
//#include "Node.h"

int compareEdge(const void *s1, const void *s2) {
    struct EdgeK *e1 = (struct EdgeK *) s1;
    struct EdgeK *e2 = (struct EdgeK *) s2;
    return int(e1->weight - e2->weight);
}

Christofides::Christofides(std::vector<Town> citiesIn) : cities(citiesIn), nodeSets(cities.size()) {
    //std::cout << "Initerar" << std::endl;
    fullGraph.v = (int) cities.size();
    if (fullGraph.v == 1) {
        std::cout << cities.front().index << std::endl;
        citiesOut.push_back(Node(cities.at(0).x, cities.at(0).y, cities.at(0).index));
        return;
    }
    fullGraph.e = (fullGraph.v * (fullGraph.v - 1)) / 2;
    fullGraph.edges = new EdgeK[fullGraph.e];
    kruskalGraph.v = (int) cities.size();
    kruskalGraph.e = fullGraph.v - 1;
    kruskalGraph.edges = new EdgeK[fullGraph.v - 1];

    addEdges();
    kruskal();

    std::vector<std::list<int>> verticesAdjacency(cities.size());
    perfectMatching(verticesAdjacency);
    hierholzer(verticesAdjacency);

    std::unordered_set<int> s;
    eulerTour.remove_if([&](int n) {
        return (s.find(n) == s.end()) ? (s.insert(n), false) : true;
    });

    for (int i : eulerTour) {
        citiesOut.push_back( Node (cities.at(i).x, cities.at(i).y, cities.at(i).index) );
    }
    //printTour(eulerTour);
    //std::cout << "Slut på min" << std::endl;
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
    }
    fullGraph.e = counter;
}

void Christofides::kruskal(){
    //Create minimal spanning tree through Kruskal's algorithm
    //std::cout << "Kruskal" << std::endl;

    std::qsort(fullGraph.edges, fullGraph.e, sizeof(struct EdgeK), compareEdge);
    int i;
    int n = 0;
    for (i = 0; i < fullGraph.e && n < kruskalGraph.e; i++) { //&& n < fullGraph.v - 1
        int u = fullGraph.edges[i].from;
        int v = fullGraph.edges[i].to;

        if (nodeSets.findParent(u) != nodeSets.findParent(v)) {
            kruskalGraph.edges[n] = fullGraph.edges[i];
            nodeSets.addDegree(u);
            nodeSets.addDegree(v);
            n++;
            nodeSets.unite(v, u);
        }
    }

}

void Christofides::perfectMatching(std::vector<std::list<int>>& verticesAdjacency) {
    //std::cout << "Perfect Matching" << std::endl;
    //Uses hungarian algorithm implemented by Shaunak Kishore (kshaunak@gmail.com) 2015
    std::vector<int> unevenVset = nodeSets.generateUnevenVset();
    int nUnevenV = unevenVset.size();

    int counter, i;
    int n = (int) nUnevenV * (nUnevenV - 1) / 2;

    struct EdgeK edges[n];
    counter = 0;
    for (i = 0; i < nUnevenV - 1 && counter < n; i++) {
        for (int j = i + 1; j < nUnevenV && counter < n; j++) {
            edges[counter].from = unevenVset.at(i);
            edges[counter].to = unevenVset.at(j);
            edges[counter].weight = cities.at(edges[counter].from).calcDistance(cities.at(edges[counter].to));
            counter++;
        }
    }

    Cost costMatrix[nUnevenV][nUnevenV];
    for (EdgeK edge : edges) {
        costMatrix[edge.to][edge.from] = edge.weight;
    }
    Hungarian hungarian(nUnevenV, costMatrix);
    Hungarian::Status status = hungarian.Solve();

    for (int i = 0; i < nUnevenV; i++) {
        verticesAdjacency.at(unevenVset.at(i)).emplace_back(hungarian.GetXMatch(i));
    }

    /*
    std::set<int> usedNodes;

    std::qsort(edges, n, sizeof(struct EdgeK), compareEdge);
    counter = 0;
    for (i = 0; (i < n) && (counter < nUnevenV / 2); i++) {
        if ( (usedNodes.count(edges[i].from) == 0) && (usedNodes.count(edges[i].to) == 0) ){
            usedNodes.insert(edges[i].from);
            usedNodes.insert(edges[i].to);
            verticesAdjacency.at(edges[i].from).emplace_back(edges[i].to);
            verticesAdjacency.at(edges[i].to).emplace_back(edges[i].from);
            counter++;
        }
    }
     */
    for (int e = 0; e < kruskalGraph.e; e++) {
        verticesAdjacency.at(kruskalGraph.edges[e].from).emplace_back(kruskalGraph.edges[e].to);
        //std::cout << "Town " << edgesIn[e].from << " adjacent to: " << verticesAdjacency.at(edgesIn[e].from).front() << std::endl;
        verticesAdjacency.at(kruskalGraph.edges[e].to).emplace_back(kruskalGraph.edges[e].from);
    }
}

void Christofides::hierholzer(std::vector<std::list<int>>& verticesAdjacency) {
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
}

void Christofides::printTour(std::list<int> inList) {
    std::cout << eulerTour.front();
    for (int i : eulerTour) {
        if (i != eulerTour.front()) {
            std::cout << "\n" << i;
        }
    }

}