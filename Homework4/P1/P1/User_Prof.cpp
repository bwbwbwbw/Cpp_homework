//
//  User_Prof.cpp
//  P1
//
//  Created by Breezewish on 14-3-21.
//  Copyright (c) 2014年 TJ. All rights reserved.
//

#include "User_Prof.h"

User_Prof::User_Prof(int _rank, string _name = "guest")
{
    uid = uid_counter++;
    rank = _rank;
    name = _name;
}

void User_Prof::login()
{
    if (logined_sessions.find(uid) != logined_sessions.end()) {
        throw "User already logged in";
    }
    
    login_times++;
    logined_sessions[uid] = true;
}

void User_Prof::logout()
{
    auto it = logined_sessions.find(uid);
    if (it == logined_sessions.end()) {
        throw "User not logged in";
    }
    
    logined_sessions.erase(it);
}

int User_Prof::getRank()
{
    return rank;
}

float User_Prof::getWonRatio()
{
    return (float)won_matches / played_matches;
}

bool User_Prof::operator==(const User_Prof &u) const
{
    return uid == u.uid;
}

bool User_Prof::operator!=(const User_Prof &u) const
{
    return uid != u.uid;
}