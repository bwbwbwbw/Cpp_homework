//
//  FormPaymentComplete.h
//  Markit
//
//  Created by Breezewish on 4/27/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormPaymentComplete_h
#define Markit_FormPaymentComplete_h

#include "FormUtils.h"
#include "Utils.h"
#include "Basket.h"

class FormPaymentComplete
{
public:
    static void show(Basket& basket)
    {
        auto grid = newtCreateGrid(1, 3);
        
        auto lblDesc = newtLabel(-1, -1, "Payment complete!");
        auto list = newtListbox(-1, -1, 10, NEWT_FLAG_BORDER | NEWT_FLAG_SCROLL);
        newtListboxSetWidth(list, 35);
        auto btnOK = newtButton(-1, -1, "OK");
        
        newtGridSetField(grid, 0, 0, NEWT_GRID_COMPONENT, lblDesc, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_COMPONENT, list, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 2, NEWT_GRID_COMPONENT, btnOK, 1, 1, 1, 0, 0, 0);
        
        for (auto& item : basket) {
            string title = "RMB " + Utils::to_string_with_precision((float)((int)item.price100 - (int)item.discount100) / 100 * item.quantity, 2) + " -- " + std::to_string(item.quantity) + " * " + item.name;
            newtListboxAppendEntry(list, title.c_str(), NULL);
        }
        newtListboxAppendEntry(list, "-----------------", NULL);
        newtListboxAppendEntry(list, ("Total: RMB " + Utils::to_string_with_precision((float)basket.getTotalPrice100() / 100, 2)).c_str(), NULL);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Complete");
        newtGridFree(grid, 1);
        
        newtRunForm(form);
        newtFormDestroy(form);
        newtPopWindow();
    }
};

#endif
