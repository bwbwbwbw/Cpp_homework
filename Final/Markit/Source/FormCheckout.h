//
//  FormCheckout.h
//  Markit
//
//  Created by Breezewish on 4/26/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormCheckout_h
#define Markit_FormCheckout_h

#include "FormUtils.h"
#include "FormAddBasket.h"
#include "FormVIP.h"
#include "Basket.h"

using std::vector;

class FormCheckout
{
public:
    static void show()
    {
        Basket basket;
        
        auto grid = newtCreateGrid(1, 4);
        
        auto lblList = newtLabel(-1, -1, "Current Basket:");
        auto list = newtListbox(-1, -1, 12, NEWT_FLAG_SCROLL | NEWT_FLAG_BORDER);
        newtListboxSetWidth(list, 40);
        newtGridSetField(grid, 0, 0, NEWT_GRID_COMPONENT, lblList, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_COMPONENT, list, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto actionGrid = newtCreateGrid(2, 1);
        auto btnAdd = newtCompactButton(-1, -1, "Add");
        auto btnRemove = newtCompactButton(-1, -1, "Remove");
        newtGridSetField(actionGrid, 0, 0, NEWT_GRID_COMPONENT, btnAdd, 0, 0, 0, 0, 0, 0);
        newtGridSetField(actionGrid, 1, 0, NEWT_GRID_COMPONENT, btnRemove, 0, 0, 0, 0, 0, 0);
        newtGridSetField(grid, 0, 2, NEWT_GRID_SUBGRID, actionGrid, 0, 0, 0, 0, 0, 0);
        
        auto buttonGrid = newtCreateGrid(2, 1);
        auto btnNext = newtButton(-1, -1, "Pay");
        auto btnCancel = newtButton(-1, -1, "Cancel");
        newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnNext, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnCancel, 1, 0, 1, 0, 0, 0);
        newtGridSetField(grid, 0, 3, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Check Out");
        newtGridFree(grid, 1);
        
        bool complete = false;
        
        do {
            auto answer = newtRunForm(form);
            
            if (answer == btnAdd) {
                FormAddBasket::show(basket, list);
            } else if (answer == btnRemove) {
                FormAddBasket::remove(basket, list);
            } else if (answer == btnCancel) {
                complete = true;
            } else if (answer == btnNext) {
                FormVIP::execute(basket); //FormPayment::execute(basket);
                complete = true;
            }
        } while (!complete);
        
        newtFormDestroy(form);
        newtPopWindow();
    }
};

#endif
