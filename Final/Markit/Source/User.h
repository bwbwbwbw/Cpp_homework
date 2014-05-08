//
//  User.h
//  Markit
//
//  Created by Breezewish on 4/24/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef __Markit__User__
#define __Markit__User__

#include <string>
#include "UserLevel.h"
#include "UserLevels.h"

using std::string;

class User
{
private:
    unsigned int  uid;
    string        name;
    int           gender;
    string        tel;
    unsigned long point1000;
public:
    unsigned int     getUID()       const;
    string           getName()      const;
    int              getGender()    const;
    string           getTel()       const;
    string           getLevel()     const;
    unsigned long    getPoint1000() const;
    const UserLevel* getAccesser()  const;
    
    User&            updatePoint1000(long addValue1000);
    
    string toString()           const;
    static User fromString(const string csvLine);
};

#endif /* defined(__Markit__User__) */
