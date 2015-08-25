//
//  main.cpp
//  CitationGraph
//
//  Created by Irene on 15-8-6.
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
using namespace std;

int main()
{
    // parameter
    int linknum = 300;

    // output files
    string f1 = "/home/yiren/Desktop/parasim/results/paradig.txt";
    ofstream file1(f1.c_str());
    if (!file1)
    {
        cout << "Error: can't open " << f1 << endl;
        exit(-1);
    }
    string f2 = "/home/yiren/Desktop/parasim/results/syntag.txt";
    ofstream file2(f2.c_str());
    if (!file2)
    {
        cout << "Error: can't open " << f2 << endl;
        exit(-1);
    }
    
    // read terms of interest from file
    string f3 = "/home/yiren/Desktop/parasim/fields.txt";
    vector<string> terms = getTerms(f3);
    
    // constructing graph
    Graph graph("/home/yiren/Desktop/parasim/FileName.txt", '\t', 'r', linknum);
    
    
    // save node info {NodeID, inlink, outlink} to file
    // last line {total_NodeNum, total_inlink, total_outlink}
    string fout = "/home/yiren/Desktop/parasim/results/LinkNum.txt";
    long total_outlink = 0;
    long total_inlink = 0;
    getLinkNum(graph, total_inlink, total_outlink, fout);
    
    // calculating paradigmatic value
    double para;
    cout << "calculating paradigmatic relations ... " << endl;
    for (int i=0; i<terms.size(); i++)
    {
        cout << "... processing node " << i+1 << endl;
        int iIndex = graph.getIndex(terms[i]);
        if (iIndex == -1) continue;
        double co_citing = 0;
        double co_cited = 0;
        for (int j=0; j<graph.nodeSet.size(); j++)
        {
            para = graph.getParaSim(iIndex, j, co_citing, co_cited);
            if (para!=0)
                file1 << graph.nodeSet[iIndex].term << "\t" << graph.nodeSet[j].term << "\t" << para << "\t" << co_citing << "\t" << co_cited << endl;
        }
    }
    
    double alpha = 0.7;
    // calculating syntagmatic value
    double syn;
    cout << "calculating syntagmatic relations ... " << endl;
    for (int i=0; i<terms.size(); i++)
    {
        cout << "... processing node " << i+1 << endl;
        int iIndex = graph.getIndex(terms[i]);
        if (iIndex == -1) continue;
        for (auto elem: graph.edgeWeightFrom[iIndex])
        {
            int jIndex = elem.first;
            syn = graph.getSyntagSim(iIndex, jIndex, alpha);
            if (syn!=0)
                file2 << graph.nodeSet[iIndex].term << "\t" << graph.nodeSet[jIndex].term << "\t" << syn <<endl;
        }
        for (auto elem: graph.edgeWeightTo[iIndex])
        {
            int jIndex = elem.first;
            syn = graph.getSyntagSim(jIndex, iIndex, alpha);
            if (syn!=0)
                file2 << graph.nodeSet[jIndex].term << "\t" << graph.nodeSet[iIndex].term << "\t" << syn <<endl;
        }
    }
    
    file1.close();
    file2.close();
    

    // get depend_score
    string in = "/home/yiren/Desktop/parasim/results/syntag.txt";
    string out  = "/home/yiren/Desktop/parasim/results/depend_score.txt";
    double threshold = 0.002;
    getDependency(in, out, threshold, '\t');
    
    // compare depend_score outcome
    // get general terms
    in = "/home/yiren/Desktop/parasim/results/depend_score.txt";
    out = "/home/yiren/Desktop/parasim/results/depend_cmp.txt";
    GetGeneral(in, out, '\t');
    
    // calculate page_rank
    // fout = "/home/yiren/Desktop/parasim/pagerank_score.txt";
    // double iter = 100;
    // GetPageRank(graph, total_outlink, fout, iter);
    
    return 0;
}
