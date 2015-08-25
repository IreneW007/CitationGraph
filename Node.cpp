//
//  Node.cpp
//  CitationGraph
//
//  Created by Irene on 15-8-6.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Node.h"

Node::Node(string term)
{
    this->term = term;
    tag = 0;
    inlink = 0;
    outlink = 0;
}