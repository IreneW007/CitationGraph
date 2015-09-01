//
//  Chain.cpp
//  CitationGraph2
//
//  Created by Irene on 8/28/15.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Chain.h"

bool isLarger(std::pair<string, double>syn1, std::pair<string, double>syn2)
{
    return syn1.second > syn2.second;
}


void getChain(string fin, string fout, string fterm, char delim)
{
    // input
    vector<string> terms;
    map< string, map<string, double> >synTo = readSim(terms, fin, 't', 0, delim);
    ifstream fBeginTerm(fterm.c_str());
    if(!fBeginTerm)
    {
        cout << "Error: can't open " << fterm << endl;
        exit(-1);
    }
    // output
    ofstream fileout(fout.c_str());
    if(!fileout)
    {
        cout << "Error: can't open " << fout << endl;
        exit(-1);
    }
    
    // parameters
    int termNum = 50;
    
    string beginTerm;
    while (getline(fBeginTerm, beginTerm))
    {
        vector<string> topFromTerm;
        vector< std::pair<string, double> > topFromTermVal(termNum);
        std::partial_sort_copy(synTo[beginTerm].begin(), synTo[beginTerm].end(), topFromTermVal.begin(), topFromTermVal.end(), isLarger);
        for (int k=0; k<topFromTermVal.size(); k++)
            topFromTerm.push_back(topFromTermVal[k].first);
        
        for (int i1=0; i1<topFromTerm.size(); i1++)
        {
            string beginTerm2 = topFromTerm[i1];
            vector<string> topFromTerm2;
            vector< std::pair<string, double> > topFromTermVal2(termNum);
            std::partial_sort_copy(synTo[beginTerm2].begin(), synTo[beginTerm2].end(), topFromTermVal2.begin(), topFromTermVal2.end(), isLarger);
            for (int k=0; k<topFromTermVal.size(); k++)
                topFromTerm2.push_back(topFromTermVal2[k].first);
            
            for (int i2=0; i2<topFromTerm2.size(); i2++)
            {
                if (find(topFromTerm.begin(), topFromTerm.end(), topFromTerm2[i2]) == topFromTerm.end())
                    continue;
                string beginTerm3 = topFromTerm2[i2];
                vector<string> topFromTerm3;
                vector< std::pair<string, double> > topFromTermVal3(termNum);
                std::partial_sort_copy(synTo[beginTerm3].begin(), synTo[beginTerm3].end(), topFromTermVal3.begin(), topFromTermVal3.end(), isLarger);
                for (int k=0; k<topFromTermVal.size(); k++)
                    topFromTerm3.push_back(topFromTermVal3[k].first);
                
                for (int i3=0; i3<topFromTerm3.size(); i3++)
                {
                    if ( (find(topFromTerm2.begin(), topFromTerm2.end(), topFromTerm3[i3]) == topFromTerm2.end()) || (find(topFromTerm.begin(), topFromTerm.end(), topFromTerm3[i3]) == topFromTerm.end()))
                    {
                        fileout << beginTerm << delim << topFromTerm[i1] << delim << topFromTerm2[i2] << endl;
                        continue;
                    }
                    fileout << beginTerm << delim << topFromTerm[i1] << delim << topFromTerm2[i2] << delim << topFromTerm3[i3] << endl;
                }
            }
        }
    }
    fileout.close();
    return;
}