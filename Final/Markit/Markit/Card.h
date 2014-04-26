//
//  Card.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__Card__
#define __Markit__Card__

#include <string>

using std::string;

class Card
{
private:
    string       cid;          // id should be non-continuous to avoid typo
    unsigned int balance100;
public:
    string       getCID()           const;
    unsigned int getBalance100()    const;
    
    Card&        updateBalance100(int addValue100);
    
    string toString()               const;
    static Card fromString(const string csvLine);
};

#endif /* defined(__Markit__Card__) */
