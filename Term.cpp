//
//  Term.cpp
//  CitationGraph2
//
//  Created by Irene on 15-8-20.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Term.h"

/*
 * read synatag/paradigmatic value from file
 * return map {fromTerm, toTerm, sim}
 * on condition that sim >= threshold
 */
map< string, map<string, double> > readSim(vector<string> &terms, string fin, double threshold, char delim)
{
    // input file
    ifstream filein(fin.c_str());
    if (!filein)
    {
        cout << "Error: can't open " << fin << endl;
        exit (-1);
    }
    
    map< string, map<string, double> > synFrom;  // {from, to, syntag}
    map< string, map<string, double> > score;
    
    // read data from file {from, to syntag}
    string line, fromTerm, toTerm, token;
    double syntag;
    cout << "reading file " << fin << endl;
    while (getline(filein, line))
    {
        stringstream sline(line.c_str());
        getline(sline, fromTerm, delim);
        getline(sline, toTerm, delim);
        getline(sline, token, delim);
        syntag = std::stod(token);
        if (syntag < threshold)
            continue;
        synFrom[fromTerm][toTerm] = syntag;
        if (find(terms.begin(), terms.end(), fromTerm) == terms.end())
            terms.push_back(fromTerm);
    }
    cout << "loading done!" << endl;
    filein.close();
    return synFrom;
}


// save node info (nodeID, inlink, outlink) to file
// last line (nodeNum, total_inlink, total_outlink)
void getLinkNum(Graph graph, long &total_inlink, long &total_outlink, string fout)
{
    // output file
    ofstream fileout(fout.c_str());
    if (!fileout)
    {
        cout << "Error: can't open " << fout << endl;
        exit (-1);
    }
    
    for (int i=0; i<graph.nodeSet.size(); i++)
    {
        fileout << graph.nodeSet[i].term << "\t" << graph.nodeSet[i].inlink << "\t" << graph.nodeSet[i].outlink << endl;
        total_inlink += graph.nodeSet[i].inlink;
        total_outlink += graph.nodeSet[i].outlink;
    }
    fileout << graph.nodeSet.size() << "\t" << total_inlink << "\t" << total_outlink << endl;
    
    fileout.close();
    return;
}


// get term names from input file
vector<string> getTerms(string filename)
{
    vector<string> terms;
    ifstream file(filename.c_str());
    if (!file)
    {
        cout << "Error: can't open " << filename << endl;
        exit(-1);
    }
    string line, fid;
    while (getline(file, line))
    {
        stringstream sline(line);
        getline(sline, fid, '\t');
        terms.push_back(fid);
    }
    file.close();
    return terms;
}
