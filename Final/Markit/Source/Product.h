//
//  Product.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__Product__
#define __Markit__Product__

#include <string>

using std::string;

class Product
{
private:
    unsigned int pid;
    string       name;
    string       from;
    unsigned int price100;  //100x price to avoid precision loss
public:
    unsigned int getPID()       const;
    string       getName()      const;
    string       getFrom()      const;
    unsigned int getPrice100()  const;
    
    string toString() const;
    static Product fromString(const string csvLine);
};

#endif /* defined(__Markit__Product__) */
