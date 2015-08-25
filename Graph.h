//
//  Graph.h
//  CitationGraph
//
//  Created by Irene on 15-8-6.
//  Copyright (c) 2015 irene. All rights reserved.
//

#ifndef CitationGraph_Graph_h
#define CitationGraph_Graph_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "Node.h"
#include "Edge.h"
using namespace std;

class Graph
{
public:
    vector<Node> nodeSet;   // nodeSet[i] = {term, inlink, outlink}
    map<string, int> nodeIndex;  // nodeIndex[term] = index
    vector< map<int, int> > edgeWeightFrom;   // edgeWeight[edge] = weight
    vector< map<int, int> > edgeWeightTo;
    
private:
    void conGraph(string filename, char delim);
    void conGraphDir(string filename, char delim);
    void updataEdgeInfo(int index1, int index2, int weight);
    
public:
    Graph(string filename, char delim, char fileOrDir, int linknum);
    void cutEdge(int k);
    int getIndex(string fid);
    double getParaSim(string term1, string term2, double &co_citing, double &co_cited);
    double getParaSim(int index1, int index2, double &co_citing, double &co_cited);
    double getSyntagSim(string term1, string term2, double alpha);
    double getSyntagSim(int index1, int index2, double alpha);
};

#endif
