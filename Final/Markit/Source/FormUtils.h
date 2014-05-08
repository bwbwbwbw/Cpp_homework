//
//  FormUtils.h
//  Markit
//
//  Created by Breezewish on 4/26/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormUtils_h
#define Markit_FormUtils_h

#include <newt.h>

class FormUtils
{
public:
    static void initialize()
    {
        newtInit();
    }
    
    static void finalize()
    {
        newtFinished();
    }
};

#endif
