//
//  Graph.cpp
//  CitationGraph
//
//  Created by Irene on 15-8-6.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Graph.h"

bool iflarger(std::pair<int, int> edgeweight1, std::pair<int, int> edgeweight2)
{
    return (edgeweight1.first > edgeweight2.first);
}

/*
 * only reserve k largest outlinks for each node
 * save edge infomation to a new map
 */
void Graph::cutEdge(int linknum)
{
    vector< map<int, int> > newEdgeWeightFrom;
    // save top-k edges for each node
    for (int fromIndex=0; fromIndex<nodeSet.size(); fromIndex++)
    {
        cout << "...cutting edges for node " << fromIndex+1 << endl;
        // find outlinks for node fromIndex
        // nodeEdge <weight, toIndex>
        vector< pair<int, int> > nodeEdge;
        for (int toIndex=0; toIndex<nodeSet.size(); toIndex++)
        {
            if (edgeWeightFrom[fromIndex].find(toIndex) == edgeWeightFrom[fromIndex].end())
                continue;
            nodeEdge.push_back(make_pair(edgeWeightFrom[fromIndex][toIndex], toIndex));
        }
        // select top-k edges
        // topkEdge <weight, toIndex>
        vector< pair<int, int> > topkEdge(linknum);
        std::partial_sort_copy(nodeEdge.begin(), nodeEdge.end(), topkEdge.begin(), topkEdge.end(), iflarger);
        // save to map
        map<int,int> newEdgeWeight;
        for (int i=0; i<topkEdge.size(); i++)
        {
            newEdgeWeight[topkEdge[i].second] = topkEdge[i].first;
            edgeWeightTo[topkEdge[i].second][fromIndex] = topkEdge[i].first;
        }
        newEdgeWeightFrom.push_back(newEdgeWeight);
    }
    edgeWeightFrom = newEdgeWeightFrom;
    return;
}


/*
 * updata edge information
 * input FromIndex, ToIndex and EdgeWeight
 */
void Graph::updataEdgeInfo(int index1, int index2, int weight)
{
    if (edgeWeightFrom[index2].find(index1) == edgeWeightFrom[index2].end())
        edgeWeightFrom[index2][index1] = weight;
    else
        edgeWeightFrom[index2][index1] += weight;
    nodeSet[index2].outlink += weight;
    nodeSet[index1].inlink += weight;
    return;
}

/*
* construct graph (from individual file)
* input file name and delimiter
* read file FFx.txt {termID, termID2, cnt}
*/
void Graph::conGraph(string filename, char delim)
{
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cout << "Error: can't open " << filename << endl;
        exit(-1);
    }
    
    string line, token, term[2];
    int cnt;
    getline(fin, line);
    while (getline(fin,line))
    {
        stringstream sline(line);
        getline(sline, term[0], delim);
        getline(sline, term[1], delim);
        getline(sline, token, delim);
        cnt = strtol(token.c_str(), 0, 10);
        
        // update nodeSet
        int index[2];
        for (int i=0; i<2; i++)
        {
            // add new node
            if (nodeIndex.find(term[i]) == nodeIndex.end())
            {
                index[i] = (int) nodeSet.size();
                Node newnode(term[i]);
                nodeSet.push_back(newnode);
                nodeIndex[term[i]] = index[i];
                if (index[i] % 5000 == 0 && index[i]!=0)
                    cout << "... " << index[i] << " nodes added!" << endl;
                map<int,int> newEdgeWeight;
                edgeWeightFrom.push_back(newEdgeWeight);
                edgeWeightTo.push_back(newEdgeWeight);
            }
            else
                index[i] = nodeIndex[term[i]];
        }
        
        // update edgeSet
        // ==================================
        // self-citation meaning???
        if (index[0] != index[1])
            updataEdgeInfo(index[0], index[1], cnt);
        // ==================================
    }
    fin.close();
    return;
}

/*
 * construct graph (from directory)
 * input directory file that contains targeted file names
 */
void Graph::conGraphDir(string filename, char delim)
{
    ifstream file(filename.c_str());
    if (!file)
    {
        cout << "Error: can't open " << filename << endl;
        exit(-1);
    }
    string fname;
    while (getline(file, fname))
    {
        cout << "... load file " << fname << endl;
        conGraph(fname, delim);
    }
    file.close();
}


/*
 * get node index
 */
int Graph::getIndex(string term)
{
    if (nodeIndex.find(term) == nodeIndex.end())
    {
        cout << "Warning: " << term << " is not in the graph!" << endl;
        return -1;
    }
    else
        return nodeIndex[term];
}


/*
* Graph constructor
*/
Graph::Graph(string filename, char delim, char fileOrDir, int linknum)
{
    cout << "constructing graph ... " << endl;
    if (fileOrDir == 'f')
        conGraph(filename, delim);
    else if (fileOrDir == 'r')
        conGraphDir(filename, delim);
    else
    {
        cout << "Error in parameter: pathname delimiter fileOrDirectory('f' or 'r')" << endl;
        exit(-1);
    }
    cutEdge(linknum);
    cout << "construction done: " << nodeSet.size() << " nodes added!" << endl;
}


/*
 * calculate paradigmatic value
 * input two node index
 */
double Graph::getParaSim(int index1, int index2, double &co_citing, double &co_cited)
{
    // invalid index
    if (index1<0 || index1>=nodeSet.size() || index2<0 || index2>=nodeSet.size())
        return 0;
    
    // create v-set (prior node)
    vector<int> vSet;
    for (auto elem: edgeWeightTo[index1])
    {
        int v = elem.first;
        if (edgeWeightTo[index2].find(v) != edgeWeightTo[index2].end())
            vSet.push_back(v);
    }
    
    // create u-set (post node)
    vector<int> uSet;
    for (auto elem: edgeWeightFrom[index1])
    {
        int u = elem.first;
        if (edgeWeightFrom[index2].find(u) != edgeWeightFrom[index2].end())
            uSet.push_back(u);
    }
        
    // no common v-set or u-set
    if (vSet.size()==0 || uSet.size()==0) return 0;
    
    double sum1 = 0;
    double sum2 = 0;
    for (int i=0; i<vSet.size(); i++)
    {
        int v = vSet[i];
        double weightv1 = (double) edgeWeightFrom[v][index1];
        double weightv2 = (double) edgeWeightFrom[v][index2];
        sum1 += weightv1 / (double) nodeSet[v].outlink * weightv2 / (double) nodeSet[index2].inlink;
        sum2 += weightv1 / (double) nodeSet[index1].inlink * weightv2 / (double) nodeSet[v].outlink;
    }
    double sum3 = 0;
    double sum4 = 0;
    for (int i=0; i<uSet.size(); i++)
    {
        int u = uSet[i];
        double weight1u = (double) edgeWeightFrom[index1][u];
        double weight2u = (double) edgeWeightFrom[index2][u];
        sum3 += (weight1u / (double) nodeSet[index1].outlink) * (weight2u / (double) nodeSet[u].inlink);
        sum4 += (weight1u / (double) nodeSet[u].inlink) * (weight2u / (double) nodeSet[index2].outlink);
    }
    co_citing = sum1 * sum2;
    co_cited = sum3 * sum4;
    return sum1*sum2*sum3*sum4 / sqrt((double)(vSet.size()*uSet.size()));
}


/*
* calculate paradigmatic value
* input two terms
*/
double Graph::getParaSim(string term1, string term2, double &co_citing, double &co_cited)
{
    int index1 = getIndex(term1);
    int index2 = getIndex(term2);
    if (index1 == -1 || index2 == -1)
    {
        if (term1 == term2) return 1;
        else return 0;
    }
    return getParaSim(index1, index2, co_citing, co_cited);
}


/*
 * calculate syntagmatic value
 * input two node index
 */
double Graph::getSyntagSim(int index1, int index2, double alpha)
{
    // invalid index
    if (index1<0 || index1>=nodeSet.size() || index2<0 || index2>=nodeSet.size())
        return 0;
    
    // parameter
    // double alpha = 0.7;
    
    // 1-step trip
    double syn1 = 0;
    if (edgeWeightFrom[index1].find(index2) != edgeWeightFrom[index1].end())
    {
        double weight12 = (double) edgeWeightFrom[index1][index2];
        syn1 = (weight12 / (double) nodeSet[index1].outlink) * (weight12 / (double) nodeSet[index2].inlink);
    }
    double syn_norm = 0;
    for (auto elem: edgeWeightFrom[index1])
    {
        int index = elem.first;
        double weight = (double) edgeWeightFrom[index1][index];
        syn_norm += weight / (double) nodeSet[index1].outlink * weight / (double) nodeSet[index].inlink;
    }
    syn1 = syn1 / syn_norm;
    
    // 2-step trip
    double syn2_for = 0;
    double syn2_back = 0;
    for (auto elem: edgeWeightFrom[index1])
    {
        int u = elem.first;
        if (edgeWeightFrom[u].find(index2) == edgeWeightFrom[u].end())
            continue;
        double weight1u = (double) edgeWeightFrom[index1][u];
        double weightu2 = (double) edgeWeightFrom[u][index2];
        syn2_for += (weight1u / (double) nodeSet[index1].outlink) * (weightu2 / (double) nodeSet[u].outlink);
        syn2_back += (weight1u / (double) nodeSet[u].inlink) * (weightu2 / (double) nodeSet[index2].inlink);
    }
    
    return alpha * syn1 + (1-alpha) * syn2_for * syn2_back;
}


/*
 * calculate syntagmatic value
 * input two terms
 */
double Graph::getSyntagSim(string term1, string term2, double alpha)
{
    int index1 = getIndex(term1);
    int index2 = getIndex(term2);
    if (index1 == -1 || index2 == -1)
    {
        if (term1 == term2) return 1;
        else return 0;
    }
    return getSyntagSim(index1, index2, alpha);
}
