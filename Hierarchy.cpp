//
//  Hierarchy.cpp
//  CitationGraph
//
//  Created by Irene on 15-8-10.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Hierarchy.h"

void GetGeneral(string fin, string fout, char delim)
{
    // IO file
    ifstream filein(fin.c_str());
    if (!filein)
    {
        cout << "Error: can't open " << fin << endl;
        exit (-1);
    }
    ofstream fileout(fout.c_str());
    if (!fileout)
    {
        cout << "Error: can't open " << fout << endl;
        exit (-1);
    }
    
    // parameters
    double thre_dependFrom = 1.3;
    double thre_dependTo = 2.0;
    
    // calculate
    // pair {from, to}
    map<string, pair<int, int>> dependNum;
    string line, fid1, fid2, token;
    double score;
    while (getline(filein, line))
    {
        stringstream sline(line);
        getline(sline, fid1, delim);
        getline(sline, fid2, delim);
        getline(sline, token, delim);
        score = std::stod(token);
        if (dependNum.find(fid1) == dependNum.end())
            dependNum[fid1] = make_pair(0, 0);
        if (dependNum.find(fid2) == dependNum.end())
            dependNum[fid2] = make_pair(0, 0);
        if (score >= thre_dependFrom)
            dependNum[fid1].first ++;
        if (score >= thre_dependTo)
            dependNum[fid2].second ++;
    }
    
    double s;
    for (auto elem: dependNum)
    {
        if (elem.second.first == 0)
            s = (double) elem.second.second;
        else
            s = (double) elem.second.second / (double) elem.second.first;
        fileout << elem.first << "\t" << s << "\t" << elem.second.first << "\t" << elem.second.second << endl;
    }
    
    filein.close();
    fileout.close();
}



/*
 * apply the idea of PageRank
 * citing nodes vote for cited nodes
 */
/*
vector<double> GetPageRank(Graph graph, long total_outlink, string fout, int iter)
{
    int iteration = 0;
    vector<double> nodeRank;
    for (int i=0; i<graph.nodeSet.size(); i++)
        nodeRank.push_back((double) graph.nodeSet[i].outlink / (double) total_outlink);
    while (iteration < iter)
    {
        for (int i=0; i<graph.nodeSet.size(); i++)
        {
            if (find(graph.edgeWeightFrom.begin(), graph.edgeWeightFrom.end(), i)!=graph.edgeWeightFrom.end())
                continue;
            nodeRank[i] = 0;
            for (auto elem: graph.edgeWeightFrom[i])
            {
                jIndex
            }
        }
        iteration ++;
        if (iteration%50 == 0) cout << "...iteration = " << iteration << endl;
    }
    return nodeRank;
}
*/

/*
 * count link number (without considering edge weight)
 * save number of absolute edge to other nodes to vector
 */

/*
vector<int> GetLinkNumber(Graph graph)
{
    vector<int> linkNum;
    for (int i=0; i<graph.nodeSet.size(); i++)
    {
        int num = 0;
        for (int j=0; j<graph.nodeSet.size(); j++)
        {
            Edge edge = Edge(j,i);
            if (graph.edgeWeight.find(edge) != graph.edgeWeight.end())
                num ++;
        }
        linkNum.push_back(num);
    }
    return linkNum;
}
*/

/*
 * calculate score on syntagmatic value
 * hoping to distinguish the "general" terms
 * score = sum_{ti}_syn(t,ti)*syn(ti,t)
 */
/*
void GetScore(string fin, string fout, Graph graph, int total_inlink, int total_outlink)
{
    vector<string> syn_fname;
    vector<double> syn_score;
    
    // IO files
    ifstream filein(fin.c_str());
    if (!filein)
    {
        cout << "Error: can't open " << fin << endl;
        exit(-1);
    }
    ofstream fileout(fout.c_str());
    if (!fileout)
    {
        cout << "Error: can't open " << fout << endl;
        exit(-1);
    }
    
    string line, fname, fname2, syn1, syn2;
    double score = 0;
    while (getline(filein, line))
    {
        stringstream sline(line);
        getline(sline, fname, ',');
        getline(sline, fname2, ',');
        getline(sline, syn1, ',');
        getline(sline, syn2, ',');
        if (syn_fname.size()==0)
        {
            syn_fname.push_back(fname);
            score = 0;
        }
        else if (fname!=syn_fname.back())
        {
            int index = graph.nodeIndex[syn_fname.back()];
            score *= (double) graph.nodeSet[index].outlink / (double) total_outlink * (double) graph.nodeSet[index].inlink / (double) total_inlink;
            syn_score.push_back(score);
            fileout << syn_fname.back() << "\t" << score << endl;
            syn_fname.push_back(fname);
            score = 0;
        }
        score += std::stod(syn1) * std::stod(syn2);
    }
    cout << syn_fname.size() << " nodes calculated!" << endl;
    fileout.close();
}
*/
