//
//  Utils.h
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_Utils_h
#define Markit_Utils_h

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using std::vector;
using std::string;

class Utils
{
public:
    static vector<string>& split(const string &s, char delim, vector<string> &elems);
    static vector<string> split(const string &s, char delim);
    static std::string to_string_with_precision(const float value, const int n = 6);
};

#endif
