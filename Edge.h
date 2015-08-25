//
//  Edge.h
//  CitationGraph
//
//  Created by Irene on 15-8-6.
//  Copyright (c) 2015 irene. All rights reserved.
//

#ifndef CitationGraph_Edge_h
#define CitationGraph_Edge_h

#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

class Edge
{
public:
    int from;
    int to;
    Edge(int fromIndex, int toIndex);
    Edge & operator=(const Edge &edge1);
    bool operator==(const Edge &edge1) const;
    bool operator<(const Edge &edge1) const;
    bool operator>(const Edge &edge1) const;
};


#endif
