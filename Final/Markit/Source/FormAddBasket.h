//
//  FormAddBasket.h
//  Markit
//
//  Created by Breezewish on 4/26/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormAddBasket_h
#define Markit_FormAddBasket_h

#include <string>
#include "Utils.h"
#include "FormUtils.h"
#include "Basket.h"
#include "Products.h"

class FormAddBasket
{
private:
    struct EntryIdCallbackData
    {
        newtComponent& entryId;
        newtComponent& entryQuantity;
        newtComponent& txtName;
        newtComponent& txtOrigin;
        newtComponent& txtPrice;
    };
    struct BasketListItemData
    {
        unsigned int pid;
        unsigned int quantity;
    };
    
    static bool addItem(Basket& basket, newtComponent& basketList, EntryIdCallbackData& entryIdData)
    {
        char* _id = newtEntryGetValue(entryIdData.entryId);
        
        try {
            unsigned int pid = std::atoi(_id);
            auto& p = Products::getFromPID(pid);
            
            try {
                char* _quantity = newtEntryGetValue(entryIdData.entryQuantity);
                unsigned int quantity = std::atoi(_quantity);
                if (quantity <= 0) {
                    throw "Invalid quantity value.";
                }
                
                basket.add(BasketItem(quantity, p));
                BasketListItemData* data = new BasketListItemData{p.getPID(), quantity};
                
                string text = std::to_string(quantity) + " * " + p.getName();
                newtListboxAppendEntry(basketList, text.c_str(), data);
            } catch (...) {
                newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)"Invalid quantity value.");
                return false;
            }
        } catch (...) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)"Goods not found.");
            return false;
        }
        
        return true;
    }
    
    static void entryIdCallback(newtComponent entry, void* data)
    {
        EntryIdCallbackData* entryIdData = (EntryIdCallbackData*)data;
        
        char* _id = newtEntryGetValue(entryIdData->entryId);
        
        try {
            unsigned int pid = std::atoi(_id);
            auto& p = Products::getFromPID(pid);
            
            float price = (float)p.getPrice100() / 100;
            
            newtTextboxSetText(entryIdData->txtName, (p.getName() + "\n ").c_str());
            newtTextboxSetText(entryIdData->txtOrigin, p.getFrom().c_str());
            newtTextboxSetText(entryIdData->txtPrice, ("RMB " + Utils::to_string_with_precision(price, 2)).c_str());
        } catch (...) {
            newtTextboxSetText(entryIdData->txtName, "/* NOT FOUND */\n ");
            newtTextboxSetText(entryIdData->txtOrigin, "/* NOT FOUND */");
            newtTextboxSetText(entryIdData->txtPrice, "/* NOT FOUND */");
        }
    }
    
public:
    static void remove(Basket& basket, newtComponent& basketList)
    {
        BasketListItemData* key = (BasketListItemData*)newtListboxGetCurrent(basketList);
        
        if (key != NULL) {
            basket.remove(key->pid, key->quantity);
            newtListboxDeleteEntry(basketList, (void*)key);
        }
    }
    
    static void show(Basket& basket, newtComponent& basketList)
    {
        const char *input_pid, *input_quantity;
        
        auto grid = newtCreateGrid(1, 2);
        
        auto fieldGrid = newtCreateGrid(2, 6);
        auto lblName = newtLabel(-1, -1, "Name:");
        auto txtName = newtTextbox(-1, -1, 50, 2, NEWT_FLAG_WRAP);
        newtGridSetField(fieldGrid, 0, 2, NEWT_GRID_COMPONENT, lblName, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(fieldGrid, 1, 2, NEWT_GRID_COMPONENT, txtName, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto lblOrigin = newtLabel(-1, -1, "Origin:");
        auto txtOrigin = newtTextbox(-1, -1, 50, 1, 0);
        newtGridSetField(fieldGrid, 0, 3, NEWT_GRID_COMPONENT, lblOrigin, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(fieldGrid, 1, 3, NEWT_GRID_COMPONENT, txtOrigin, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto lblPrice = newtLabel(-1, -1, "Price each:");
        auto txtPrice = newtTextbox(-1, -1, 50, 1, 0);
        newtGridSetField(fieldGrid, 0, 4, NEWT_GRID_COMPONENT, lblPrice, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(fieldGrid, 1, 4, NEWT_GRID_COMPONENT, txtPrice, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto lblId = newtLabel(-1, -1, "ID:");
        auto entryId = newtEntry(-1, -1, NULL, 50, &input_pid, NEWT_ENTRY_SCROLL);
        newtGridSetField(fieldGrid, 0, 0, NEWT_GRID_COMPONENT, lblId, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(fieldGrid, 1, 0, NEWT_GRID_COMPONENT, entryId, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto lblQuantity = newtLabel(-1, -1, "Quantity:");
        auto entryQuantity = newtEntry(-1, -1, "1", 50, &input_quantity, NEWT_ENTRY_SCROLL);
        newtGridSetField(fieldGrid, 0, 1, NEWT_GRID_COMPONENT, lblQuantity, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(fieldGrid, 1, 1, NEWT_GRID_COMPONENT, entryQuantity, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        EntryIdCallbackData entryIdData = { entryId, entryQuantity, txtName, txtOrigin, txtPrice };
        newtComponentAddCallback(entryId, entryIdCallback, &entryIdData);
        
        auto buttonGrid = newtCreateGrid(2, 1);
        auto btnAdd = newtButton(-1, -1, "Add");
        auto btnCancel = newtButton(-1, -1, "Cancel");
        newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnAdd, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnCancel, 1, 0, 1, 0, 0, 0);
        
        newtGridSetField(grid, 0, 0, NEWT_GRID_SUBGRID, fieldGrid, 0, 0, 0, 0, 0, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Add to Basket");
        newtGridFree(grid, 1);
        
        bool complete = false;
        do {
            auto answer = newtRunForm(form);
            if (answer == btnCancel) {
                complete = true;
            } else if (answer == btnAdd) {
                complete = addItem(basket, basketList, entryIdData);
            }
        } while (!complete);
        
        
        newtFormDestroy(form);
        newtPopWindow();
    }
};

#endif
