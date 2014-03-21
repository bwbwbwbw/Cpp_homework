//
//  User_Prof.h
//  P1
//
//  Created by Breezewish on 14-3-21.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#ifndef __P1__User_Prof__
#define __P1__User_Prof__

#include <string>
#include <map>

using std::string;

std::map<int, bool> logined_sessions;
int uid_counter = 0;

class User_Prof
{
public:
    enum {
        BEGINNER,
        PROFESSIONAL,
        EXPERT
    };
    
    User_Prof(int _rank, string _name);
    void login();
    void logout();
    int getRank();
    float getWonRatio();
    bool operator==(const User_Prof &u) const;
    bool operator!=(const User_Prof &u) const;
private:
    string name;
    int login_times;
    int played_matches;
    int won_matches;
    int rank;
    int uid;
};

#endif /* defined(__P1__User_Prof__) */
