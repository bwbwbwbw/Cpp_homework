//
//  Cards.h
//  Markit
//
//  Created by Breezewish on 4/25/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_Cards_h
#define Markit_Cards_h

#include <fstream>
#include <string>
#include <map>
#include "Card.h"

using std::map;

class Cards
{
private:
    static map<string, Card> cards;
public:
    static Card& getFromCID(const string cid);
    static void importFromFile(const string file);
    static void exportToFile(const string file);
};

#endif
