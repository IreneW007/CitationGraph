//
//  Term.h
//  CitationGraph2
//
//  Created by Irene on 15-8-20.
//  Copyright (c) 2015 irene. All rights reserved.
//

#ifndef __CitationGraph2__Term__
#define __CitationGraph2__Term__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include "Graph.h"
using namespace std;

vector<string> getTerms(string filename);
void getLinkNum(Graph graph, long &total_inlink, long &total_outlink, string fout);
map< string, map<string, double> > readSim(vector<string> &terms, string fin, char fromORto, double threshold, char delim)

#endif /* defined(__CitationGraph2__Term__) */
