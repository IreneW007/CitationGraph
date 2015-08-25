//
//  Node.h
//  CitationGraph
//
//  Created by Irene on 15-8-6.
//  Copyright (c) 2015 irene. All rights reserved.
//

#ifndef CitationGraph_Node_h
#define CitationGraph_Node_h

#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

class Node
{
public:
    string term;
    bool tag;
    int inlink;     // total inlink weight
    int outlink;    // total outlink weight
    Node(string term); // constructor
};

#endif
