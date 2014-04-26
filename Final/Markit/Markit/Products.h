//
//  Products.h
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_Products_h
#define Markit_Products_h

#include <fstream>
#include <string>
#include <map>
#include "Product.h"

using std::map;

class Products
{
private:
    static map<unsigned int, Product> products;
public:
    static Product& getFromPID(unsigned int pid);
    static void importFromFile(const string file);
    static void exportToFile(const string file);
};

#endif
