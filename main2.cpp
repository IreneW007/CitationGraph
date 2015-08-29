//
//  main2.cpp
//  CitationGraph2
//
//  Created by Irene on 8/28/15.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>
#include "Node.h"
#include "Edge.h"
#include "Graph.h"
#include "Term.h"
#include "Score.h"
#include "Hierarchy.h"
#include "Chain.h"
using namespace std;

int main()
{
    string f1 = "/home/yiren/Desktop/parasim/results0/syntag.txt";
    string f2 = "/home/yiren/Desktop/parasim/results0/chains.txt";
    string f3 = "/home/yiren/Desktop/parasim/data/terms.txt";
    
    getChain(f1, f2, f3, '\t');
    
    return 0;
}
