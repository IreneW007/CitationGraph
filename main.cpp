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
    string f3 = "/home/yiren/Desktop/parasim/data/fields.txt";
    vector<string> terms = getTerms(f3);
     
    // constructing graph
    Graph graph("/home/yiren/Desktop/parasim/data/nFF1to75.txt", '\t', 'f', linknum);
    
    /*
    // save node info {NodeID, inlink, outlink} to file
    // last line {total_NodeNum, total_inlink, total_outlink}
    string fout = "/home/yiren/Desktop/parasim/results/LinkNum.txt";
    long total_outlink = 0;
    long total_inlink = 0;
    getLinkNum(graph, total_inlink, total_outlink, fout);
    */
    
    // calculating syntagmatic value
    double alpha = 0.7;
    double syn = 0;
    cout << "calculating syntagmatic relations ... " << endl;
    // for (int i=0; i<terms.size(); i++)
    for (int i=0; i<graph.nodeSet.size(); i++)
    {
        cout << "... processing node " << i+1 << endl;
        // int iIndex = graph.getIndex(terms[i]);
        // if (iIndex == -1) continue;
        int iIndex = i;
        
        // from node_i
        vector<int> toIndex;
        vector<double> syn1;
        double sum1 = 0;
        for (auto elem: graph.edgeWeightFrom[iIndex])
        {
            int jIndex = elem.first;
            syn = graph.getSyntagSim(iIndex, jIndex, alpha);
            if (syn!=0)
            {
                toIndex.push_back(jIndex);
                syn1.push_back(syn);
                sum1 += syn;
            }
        }
        // normalize and output
        for (int k=0; k<toIndex.size(); k++)
        {
            file2 << graph.nodeSet[iIndex].term << "\t" << graph.nodeSet[toIndex[k]].term << "\t" << syn1[k]/sum1 << endl;
        }
        
    /*
        // to node_i
        vector<int> fromIndex;
        vector<double> syn2;
        double sum2 = 0;
        for (auto elem: graph.edgeWeightTo[iIndex])
        {
            int jIndex = elem.first;
            syn = graph.getSyntagSim(jIndex, iIndex, alpha);
            if (syn!=0)
            {
                fromIndex.push_back(jIndex);
                syn2.push_back(syn);
                sum2 += syn;
            }
        }
        for (int k=0; k<fromIndex.size(); k++)
        {
            file2 << graph.nodeSet[fromIndex[k]].term << "\t" << graph.nodeSet[iIndex].term << "\t" << syn2[k]/sum2 << endl;
        }
     */
    }
    
    /*
     // calculating paradigmatic value
     double para;
     cout << "calculating paradigmatic relations ... " << endl;
     for (int i=0; i<terms.size(); i++)
     {
         cout << "... processing node " << i+1 << endl;
         int iIndex = graph.getIndex(terms[i]);
         if (iIndex == -1) continue;
         for (int j=0; j<graph.nodeSet.size(); j++)
         {
             para = graph.getParaSim(iIndex, j);
             if (para!=0)
                 file1 << graph.nodeSet[iIndex].term << "\t" << graph.nodeSet[j].term << "\t" << para << endl;
         }

    }
     */
    
    file1.close();
    file2.close();
    
    string in = "/home/yiren/Desktop/parasim/results/syntag.txt";
    string out_from = "/home/yiren/Desktop/parasim/results/syn_from.txt";
    string out_eq = "/home/yiren/Desktop/parasim/results/syn_eq.txt";
    getDependency(in, out_from, out_eq, '\t');
    
    
    // get depend_score
    in = "/home/yiren/Desktop/parasim/results/syntag.txt";
    string out  = "/home/yiren/Desktop/parasim/results/depend_score.txt";
    double threshold = 0.001;
    SyntagCmp(in, out, threshold, '\t');
    
    
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
