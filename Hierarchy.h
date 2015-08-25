//
//  Hierarchy.h
//  CitationGraph
//
//  Created by Irene on 15-8-9.
//  Copyright (c) 2015 irene. All rights reserved.
//

#ifndef CitationGraph_Hierarchy_h
#define CitationGraph_Hierarchy_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include "Graph.h"
#include "Score.h"
using namespace std;

void GetGeneral(string fin, string fout, char delim);
void GetScore(string fin, string fout, Graph graph, int total_inlink, int total_outlink);
vector<double> GetPageRank(Graph graph, long total_outlink, string fout, int iter);
vector<int> GetLinkNumber(Graph graph);
vector<int> GetGeneralTerm(Graph graph);

#endif
