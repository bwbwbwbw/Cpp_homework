//
//  FormVIP.h
//  Markit
//
//  Created by Breezewish on 4/26/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormVIP_h
#define Markit_FormVIP_h

#include <string>
#include "Utils.h"
#include "FormUtils.h"
#include "FormPayment.h"
#include "Basket.h"
#include "Users.h"
#include "UserLevel.h"

class FormVIP
{
private:
    struct EntryIdCallbackData
    {
        Basket& basket;
        newtComponent& entryId;
        newtComponent& txtTotal;
        newtComponent& txtName;
        newtComponent& txtLevel;
        newtComponent& txtTel;
    };
    
    static void entryIdCallback(newtComponent entry, void* data)
    {
        EntryIdCallbackData* entryIdData = (EntryIdCallbackData*)data;
        
        char* _id = newtEntryGetValue(entryIdData->entryId);
        
        try {
            unsigned int uid = std::atoi(_id);
            auto& u = Users::getFromUID(uid);
            
            newtTextboxSetText(entryIdData->txtLevel, (u.getLevel() + " (Point: " + Utils::to_string_with_precision((float)u.getPoint1000() / 1000, 3) + ")").c_str());
            
            auto gender = u.getGender();
            string gender_str;
            if (gender == 0) {
                gender_str = "Other";
            } else if (gender == 1) {
                gender_str = "Male";
            } else {
                gender_str = "Female";
            }
            
            float price = (float)entryIdData->basket.getTotalPrice100() / 100;
            float price2 = (float)u.getAccesser()->getDiscountBasket(entryIdData->basket).getTotalPrice100() / 100;
            
            newtTextboxSetText(entryIdData->txtName, (u.getName() + " (" + gender_str + ")").c_str());
            newtTextboxSetText(entryIdData->txtTel, u.getTel().c_str());
            newtTextboxSetText(entryIdData->txtTotal, ("RMB " + Utils::to_string_with_precision(price2, 2) + " (discount: RMB " + Utils::to_string_with_precision(price - price2, 2) + ")").c_str());
        } catch (...) {
            float price = (float)entryIdData->basket.getTotalPrice100() / 100;
            
            newtTextboxSetText(entryIdData->txtName, "/* NOT FOUND */");
            newtTextboxSetText(entryIdData->txtTel, "/* NOT FOUND */");
            newtTextboxSetText(entryIdData->txtLevel, "/* NOT FOUND */");
            newtTextboxSetText(entryIdData->txtTotal, ("RMB " + Utils::to_string_with_precision(price, 2)).c_str());
        }
    }
    
    static bool useCard(EntryIdCallbackData& entryIdData)
    {
        char* _id = newtEntryGetValue(entryIdData.entryId);
        
        try {
            unsigned int uid = std::atoi(_id);
            auto& u = Users::getFromUID(uid);
            
            auto accesser = u.getAccesser();
            auto basket_new = accesser->getDiscountBasket(entryIdData.basket);
            FormPayment::execute(basket_new);
            
            //TODO: check whether update successfully
            u.updatePoint1000(accesser->getBonusPoint1000(entryIdData.basket));
        } catch(...) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)"VIPUser not found.");
            return false;
        }
        
        return true;
    }
    
public:
    static void execute(Basket& basket)
    {
        const char *input_cid;
        
        auto grid = newtCreateGrid(1, 4);
        
        auto amountGrid = newtCreateGrid(2, 1);
        auto lblTotal = newtLabel(-1, -1, "Total:  ");
        auto txtTotal = newtTextbox(-1, -1, 40, 1, 0);
        newtGridSetField(amountGrid, 0, 0, NEWT_GRID_COMPONENT, lblTotal, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 0, NEWT_GRID_COMPONENT, txtTotal, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 0, NEWT_GRID_SUBGRID, amountGrid, 0, 0, 0, 0, 0, 0);
        
        auto txtDesc = newtTextbox(-1, -1, 30, 1, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_COMPONENT, txtDesc, 0, 1, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtTextboxSetText(txtDesc, "-- VIP DISCOUNT --");
        
        auto userGrid = newtCreateGrid(2, 4);
        
        auto lblId = newtLabel(-1, -1, "Card ID:");
        auto entryId = newtEntry(-1, -1, NULL, 20, &input_cid, NEWT_ENTRY_SCROLL);
        newtGridSetField(userGrid, 0, 0, NEWT_GRID_COMPONENT, lblId, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(userGrid, 1, 0, NEWT_GRID_COMPONENT, entryId, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto lblLevel = newtLabel(-1, -1, "Level:");
        auto txtLevel = newtTextbox(-1, -1, 40, 1, 0);
        newtGridSetField(userGrid, 0, 1, NEWT_GRID_COMPONENT, lblLevel, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(userGrid, 1, 1, NEWT_GRID_COMPONENT, txtLevel, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto lblName = newtLabel(-1, -1, "Name:");
        auto txtName = newtTextbox(-1, -1, 40, 1, 0);
        newtGridSetField(userGrid, 0, 2, NEWT_GRID_COMPONENT, lblName, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(userGrid, 1, 2, NEWT_GRID_COMPONENT, txtName, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        auto lblTel = newtLabel(-1, -1, "Tel:");
        auto txtTel = newtTextbox(-1, -1, 40, 1, 0);
        newtGridSetField(userGrid, 0, 3, NEWT_GRID_COMPONENT, lblTel, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(userGrid, 1, 3, NEWT_GRID_COMPONENT, txtTel, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        
        EntryIdCallbackData entryIdData = { basket, entryId, txtTotal, txtName, txtLevel, txtTel };
        newtComponentAddCallback(entryId, entryIdCallback, &entryIdData);
        
        auto buttonGrid = newtCreateGrid(2, 1);
        auto btnUse = newtButton(-1, -1, "Use");
        auto btnSkip = newtButton(-1, -1, "Skip");
        newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnUse, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnSkip, 1, 0, 1, 0, 0, 0);
        
        newtGridSetField(grid, 0, 2, NEWT_GRID_SUBGRID, userGrid, 0, 0, 0, 0, 0, 0);
        newtGridSetField(grid, 0, 3, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Discount");
        newtGridFree(grid, 1);
        
        bool complete = false;
        
        do {
            auto answer = newtRunForm(form);
            if (answer == btnSkip) {
                FormPayment::execute(basket);
                complete = true;
            } else if (answer == btnUse) {
                complete = useCard(entryIdData);
            }
        } while (!complete);
        
        newtFormDestroy(form);
        newtPopWindow();
    }
};

#endif
