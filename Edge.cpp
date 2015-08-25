//
//  Edge.cpp
//  CitationGraph
//
//  Created by Irene on 15-8-6.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Edge.h"

Edge::Edge(int fromIndex, int toIndex)
{
    from = fromIndex;
    to = toIndex;
}

// edge:= edge1, assign value
Edge & Edge::operator=(const Edge &edge1)
{
    from = edge1.from;
    to = edge1.to;
    return *this;
}

bool Edge::operator==(const Edge &edge1) const
{
    if (from == edge1.from && to == edge1.to)
        return 1;
    else
        return 0;
}

bool Edge::operator<(const Edge &edge1) const
{
    if (from < edge1.from)
        return 1;
    else if (from == edge1.from && to < edge1.to)
        return 1;
    return 0;
}

bool Edge::operator>(const Edge &edge1) const
{
    if (from > edge1.from)
        return 1;
    else if (from == edge1.from && to > edge1.to)
        return 1;
    return 0;
}
