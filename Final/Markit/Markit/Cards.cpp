//
//  Cards.cpp
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#include "Cards.h"

map<string, Card> Cards::cards;

Card& Cards::getFromCID(const string cid)
{
    auto it = cards.find(cid);
    if (it == cards.end()) {
        throw string("Gift Card not found");
    }
    
    return it->second;
}

void Cards::importFromFile(const string file)
{
    std::ifstream fin;
    fin.open(file);
    
    string line;
    
    cards.clear();
    
    while (fin.good()) {
        std::getline(fin, line);
        try {
            auto c = Card::fromString(line);
            cards[c.getCID()] = c;
        } catch(...) {}
    }
    
    fin.close();
}

void Cards::exportToFile(const string file)
{
    std::ofstream fout;
    fout.open(file);
    
    for (auto& pair : cards) {
        fout << pair.second.toString() << std::endl;
    }
    
    fout.close();
}
