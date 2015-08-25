//
//  Score.h
//  CitationGraph2
//
//  Created by Irene on 15-8-22.
//  Copyright (c) 2015 irene. All rights reserved.
//

#ifndef __CitationGraph2__Score__
#define __CitationGraph2__Score__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include "Term.h"
using namespace std;

void getDependency(string fin, string fout, double threshold, char delim);

#endif /* defined(__CitationGraph2__Score__) */
