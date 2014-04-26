//
//  Products.cpp
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "Products.h"

map<unsigned int, Product> Products::products;

Product& Products::getFromPID(unsigned int pid)
{
    auto it = products.find(pid);
    if (it == products.end()) {
        throw string("Goods not found");
    }
    
    return it->second;
}

void Products::importFromFile(const string file)
{
    std::ifstream fin;
    fin.open(file);
    
    string line;
    
    products.clear();
    
    while (fin.good()) {
        std::getline(fin, line);
        try {
            auto p = Product::fromString(line);
            products[p.getPID()] = p;
        } catch(...) {}
    }
    
    fin.close();
}

void Products::exportToFile(const string file)
{
    std::ofstream fout;
    fout.open(file);
    
    for (auto& pair : products) {
        fout << pair.second.toString() << std::endl;
    }
    
    fout.close();
}
