//
//  Score.cpp
//  CitationGraph2
//
//  Created by Irene on 15-8-22.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Score.h"

/* 
 * calculate depedency score
 * score = syn(A->B) / syn(B->A) (where syn>threshold, score>1)
 * input syntagmatic file {FID1, FID2, SIM}
 * output dependency score to file {FID1, FID2, Score}
 */
void getDependency(string fin, string fout, double threshold, char delim)
{
    vector<string> terms;
    map< string, map<string, double> >synFrom = readSim(terms, fin, threshold, delim);
    // output file
    ofstream fileout(fout.c_str());
    if (!fileout)
    {
        cout << "Error: can't open " << fout << endl;
        exit (-1);
    }
    
    // calculate dependency score
    // write to file
    double synscore;
    map< string, map<string, double> > score;
    for (int i=0; i<terms.size(); i++)
    {
        string term1 = terms[i];
        for(auto elem: synFrom[term1])
        {
            cout << "... processing term " << term1 << endl;
            string term2 = elem.first;
            if (synFrom.find(term2) == synFrom.end())
                continue;
            if (synFrom[term2].find(term1) == synFrom[term2].end())
                continue;
            synscore = elem.second / synFrom[term2][term1];
            if (synscore>1)
            {
                score[term1][term2] = synscore;
                fileout << term1 << "\t" << term2 << "\t" << synscore << endl;
            }
        }
    }
    
    fileout.close();
    return;
}