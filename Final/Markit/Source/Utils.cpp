//
//  Utils.cpp
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "Utils.h"

vector<string>& Utils::split(const string &s, char delim, vector<string> &elems)
{
    std::stringstream ss(s);
    string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> Utils::split(const string &s, char delim)
{
    vector<string> elems;
    Utils::split(s, delim, elems);
    return elems;
}

std::string Utils::to_string_with_precision(const float value, const int n)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << value;
    return out.str();
}