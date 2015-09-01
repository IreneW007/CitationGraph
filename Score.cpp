//
//  Score.cpp
//  CitationGraph2
//
//  Created by Irene on 15-8-22.
//  Copyright (c) 2015 irene. All rights reserved.
//

#include "Score.h"

void getDependency(string fin, string fout_to, string fout_eq, char delim)
{
    vector<string> terms;
    map< string, map<string, double> >synTo = readSim(terms, fin, 't', 0, delim);
    
    // output file
    ofstream out_to(fout_to.c_str());
    if (!out_to)
    {
        cout << "Error: can't open " << fout_to << endl;
        exit (-1);
    }
    ofstream out_eq(fout_eq.c_str());
    if (!out_eq)
    {
        cout << "Error: can't open " << fout_eq << endl;
        exit (-1);
    }
    
    // parameters
    double threshold = 1.5;
    double syn_threshold = 0.001;
    
    // get dependency probability
    for (int i=0; i<terms.size(); i++)
    {
        cout << "... processing term " << i << endl;
        // variables
        string term1 = terms[i];
        double syn12, syn21, score;
        vector<string> fromTerm, eqTerm;
        vector<double> fromSyn, eqSyn;
        double sum = 0, eqSum = 0;
        
        // calcultion
        for (auto elem: synTo[term1])
        {
            string term2 = elem.first;
            syn12 = elem.second;
            if (synTo.find(term2) != synTo.end() && synTo[term2].find(term1) != synTo[term2].end())
            {
                syn21 = synTo[term2][term1];
                if (syn21 > syn_threshold && syn12/syn21 > threshold)
                {
                    score = syn12 * syn12/(syn12+syn21);
                    fromTerm.push_back(term2);
                    fromSyn.push_back(score);
                    sum += score;
                }
                else if ((syn12/syn21<=threshold && syn12/syn21>=1) || (syn21/syn12<=threshold && syn21/syn12>=1))
                {
                    score = syn12 * syn21 / (syn12+syn21);
                    eqTerm.push_back(term2);
                    eqSyn.push_back(score);
                    eqSum += score;
                    sum += score;
                }
            }
            else
            {
                score = syn12;
                fromTerm.push_back(term2);
                fromSyn.push_back(score);
                sum += score;
            }
        }
        
        // output
        for (int k=0; k<fromTerm.size(); k++)
            out_to << term1 << delim << fromTerm[k] << delim << fromSyn[k]/sum << endl;
        for (int k=0; k<eqTerm.size(); k++)
            out_eq << term1 << delim << eqTerm[k] << delim << eqSyn[k]/sum << endl;
    }
    
    out_eq.close();
    out_to.close();
    return;
}



/* 
 * calculate depedency score
 * score = syn(A->B) / syn(B->A) (where syn>threshold, score>1)
 * input syntagmatic file {FID1, FID2, SIM}
 * output dependency score to file {FID1, FID2, Score}
 */
void SyntagCmp(string fin, string fout, double threshold, char delim)
{
    vector<string> terms;
    map< string, map<string, double> >synFrom = readSim(terms, fin, 'f', threshold, delim);
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