//
//  FormPayment.h
//  Markit
//
//  Created by Breezewish on 4/26/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormPayment_h
#define Markit_FormPayment_h

#include <cmath>
#include "FormUtils.h"
#include "FormPaymentComplete.h"
#include "Basket.h"
#include "Users.h"

class FormPayment
{
private:
    struct PaymentProperties
    {
        unsigned int total100;
        unsigned int complete100;
    };
    struct EntryCashPayAmountCallbackData
    {
        PaymentProperties& pp;
        newtComponent& entryPayAmount;
        newtComponent& entryPayReceive;
        newtComponent& txtChange;
    };
    struct EntryBankCardPayAmountCallbackData
    {
        PaymentProperties& pp;
        newtComponent& entryPayAmount;
    };
    struct EntryGiftCardPayAmountCallbackData
    {
        PaymentProperties& pp;
        newtComponent& entryPayAmount;
        newtComponent& entryCardId;
        newtComponent& txtCardBalance;
    };
    
    static void entryCashPayAmountCallback(newtComponent entry, void* _data)
    {
        EntryCashPayAmountCallbackData* data = (EntryCashPayAmountCallbackData*)_data;
        
        char *_pay = newtEntryGetValue(data->entryPayAmount);
        
        try {
            float pay = std::atof(_pay);
            if (std::isnan(pay) || std::isinf(pay)) {
                throw "Invalid paying amount";
            }
            if (pay * 100 > (data->pp.total100 - data->pp.complete100)) {
                throw "Invalid paying amount";
            }
            
            char *_receive = newtEntryGetValue(data->entryPayReceive);
            float receive = std::atof(_receive);
            if (std::isnan(pay) || std::isinf(pay)) {
                throw "Invalid received amount";
            }
            
            if (receive >= pay) {
                newtTextboxSetText(data->txtChange, Utils::to_string_with_precision(receive - pay, 2).c_str());
            } else {
                newtTextboxSetText(data->txtChange, "0.00");
            }
        } catch (string e) {
            newtTextboxSetText(data->txtChange, const_cast<char*>(e.c_str()));
        } catch (...) {
            newtTextboxSetText(data->txtChange, "Invalid input");
        }
    }
    
    static void entryGiftCardIdCallback(newtComponent entry, void* _data)
    {
        EntryGiftCardPayAmountCallbackData* data = (EntryGiftCardPayAmountCallbackData*)_data;
        
        char *_cardId = newtEntryGetValue(data->entryCardId);
        
        try {
            auto& card = Cards::getFromCID(string(_cardId));
            newtTextboxSetText(data->txtCardBalance, Utils::to_string_with_precision((float)card.getBalance100() / 100, 2).c_str());
        } catch (string e) {
            newtTextboxSetText(data->txtCardBalance, "/* NOT FOUND */");
        } catch (...) {
            newtTextboxSetText(data->txtCardBalance, "Unknown error");
        }
    }
    
    static bool payBank(EntryBankCardPayAmountCallbackData& data)
    {
        char *_pay = newtEntryGetValue(data.entryPayAmount);
        
        try {
            float pay = std::atof(_pay);
            if (std::isnan(pay)) {
                throw "Invalid paying amout";
            }
            if (pay * 100 > (data.pp.total100 - data.pp.complete100)) {
                throw "Paying amount should be less than or equal to " + Utils::to_string_with_precision((float)(data.pp.total100 - data.pp.complete100) / 100, 2);
            }
            
            data.pp.complete100 += pay * 100;
        } catch (string e) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)e.c_str());
            return false;
        } catch (...) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)"Unknown error");
            return false;
        }
        
        return true;
    }
    
    static bool payCash(EntryCashPayAmountCallbackData& data)
    {
        char *_pay = newtEntryGetValue(data.entryPayAmount);
        
        try {
            float pay = std::atof(_pay);
            if (std::isnan(pay)) {
                throw "Invalid paying amout";
            }
            if (pay * 100 > (data.pp.total100 - data.pp.complete100)) {
                throw "Paying amount should be less than or equal to " + Utils::to_string_with_precision((float)(data.pp.total100 - data.pp.complete100) / 100, 2);
            }
            
            char *_receive = newtEntryGetValue(data.entryPayReceive);
            float receive = std::atof(_receive);
            if (std::isnan(pay)) {
                throw "Invalid received amount";
            }
            
            if (receive >= pay) {
                data.pp.complete100 += pay * 100;
            } else {
                data.pp.complete100 += receive * 100;
            }
        } catch (string e) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)e.c_str());
            return false;
        } catch (...) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)"Unknown error");
            return false;
        }
        
        return true;
    }
    
    static bool payGift(EntryGiftCardPayAmountCallbackData& data)
    {
        char *_pay = newtEntryGetValue(data.entryPayAmount);
        
        try {
            float pay = std::atof(_pay);
            if (std::isnan(pay)) {
                throw "Invalid paying amout";
            }
            if (pay * 100 > (data.pp.total100 - data.pp.complete100)) {
                throw "Paying amount should be less than or equal to " + Utils::to_string_with_precision((float)(data.pp.total100 - data.pp.complete100) / 100, 2);
            }
            
            char *_id = newtEntryGetValue(data.entryCardId);
            
            try {
                auto& card = Cards::getFromCID(string(_id));
                
                card.updateBalance100(-pay * 100);
                data.pp.complete100 += pay * 100;
            } catch (string e) {
                newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)e.c_str());
                return false;
            }
        } catch (string e) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)e.c_str());
            return false;
        } catch (...) {
            newtWinMessage((char*)"Markit Error", (char*)"OK", (char*)"Unknown error");
            return false;
        }
        
        return true;
    }
    
public:
    static void showCash(PaymentProperties& pp)
    {
        const char *input_payamount, *input_payreceive;
        
        auto grid = newtCreateGrid(1, 2);
        
        auto amountGrid = newtCreateGrid(2, 4);
        auto lblNeedPay = newtLabel(-1, -1, "Need pay:");
        auto txtNeedPay = newtTextbox(-1, -1, 20, 1, 0);
        newtTextboxSetText(txtNeedPay, Utils::to_string_with_precision((float)(pp.total100 - pp.complete100) / 100, 2).c_str());
        auto lblPayAmount = newtLabel(-1, -1, "Pay amount:");
        auto entryPayAmount = newtEntry(-1, -1, Utils::to_string_with_precision((float)(pp.total100 - pp.complete100) / 100, 2).c_str(), 20, &input_payamount, 0);
        auto lblPayReceive = newtLabel(-1, -1, "Cash received:");
        auto entryPayReceive = newtEntry(-1, -1, NULL, 20, &input_payreceive, 0);
        auto lblChange = newtLabel(-1, -1, "Change:");
        auto txtChange = newtTextbox(-1, -1, 20, 1, 0);
        newtGridSetField(amountGrid, 0, 0, NEWT_GRID_COMPONENT, lblNeedPay, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 0, NEWT_GRID_COMPONENT, txtNeedPay, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 1, NEWT_GRID_COMPONENT, lblPayAmount, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 1, NEWT_GRID_COMPONENT, entryPayAmount, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 2, NEWT_GRID_COMPONENT, lblPayReceive, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 2, NEWT_GRID_COMPONENT, entryPayReceive, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 3, NEWT_GRID_COMPONENT, lblChange, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 3, NEWT_GRID_COMPONENT, txtChange, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 0, NEWT_GRID_SUBGRID, amountGrid, 0, 0, 0, 0, 0, 0);
        
        EntryCashPayAmountCallbackData data = {pp, entryPayAmount, entryPayReceive, txtChange};
        newtComponentAddCallback(entryPayAmount, entryCashPayAmountCallback, &data);
        newtComponentAddCallback(entryPayReceive, entryCashPayAmountCallback, &data);
        
        auto buttonGrid = newtCreateGrid(3, 1);
        auto btnPay = newtButton(-1, -1, "Cash Pay");
        auto btnCancel = newtButton(-1, -1, "Cancel");
        newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnPay, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnCancel, 1, 0, 1, 0, 0, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Cash Payment");
        newtGridFree(grid, 1);
        
        bool complete = 0;
        
        do {
            auto answer = newtRunForm(form);
            
            if (answer == btnCancel) {
                complete = true;
            } else if (answer == btnPay) {
                complete = payCash(data);
            }
        } while (!complete);
        
        newtFormDestroy(form);
        newtPopWindow();
    }
    
    static void showBankCard(PaymentProperties& pp)
    {
        const char *input_cardid, *input_cardname, *input_payamount;
        
        auto grid = newtCreateGrid(1, 2);
        
        auto amountGrid = newtCreateGrid(2, 4);
        auto lblNeedPay = newtLabel(-1, -1, "Need pay:");
        auto txtNeedPay = newtTextbox(-1, -1, 20, 1, 0);
        newtTextboxSetText(txtNeedPay, Utils::to_string_with_precision((float)(pp.total100 - pp.complete100) / 100, 2).c_str());
        auto lblPayAmount = newtLabel(-1, -1, "Pay amount:");
        auto entryPayAmount = newtEntry(-1, -1, Utils::to_string_with_precision((float)(pp.total100 - pp.complete100) / 100, 2).c_str(), 20, &input_payamount, 0);
        auto lblCardId = newtLabel(-1, -1, "Bank CardID:");
        auto entryCardId = newtEntry(-1, -1, NULL, 20, &input_cardid, 0);
        auto lblCardName = newtLabel(-1, -1, "Bank CardName:");
        auto entryCardName = newtEntry(-1, -1, NULL, 20, &input_cardname, 0);
        
        newtGridSetField(amountGrid, 0, 0, NEWT_GRID_COMPONENT, lblNeedPay, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 0, NEWT_GRID_COMPONENT, txtNeedPay, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 1, NEWT_GRID_COMPONENT, lblPayAmount, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 1, NEWT_GRID_COMPONENT, entryPayAmount, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 2, NEWT_GRID_COMPONENT, lblCardId, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 2, NEWT_GRID_COMPONENT, entryCardId, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 3, NEWT_GRID_COMPONENT, lblCardName, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 3, NEWT_GRID_COMPONENT, entryCardName, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 0, NEWT_GRID_SUBGRID, amountGrid, 0, 0, 0, 0, 0, 0);
        
        EntryBankCardPayAmountCallbackData data = {pp, entryPayAmount};
        
        auto buttonGrid = newtCreateGrid(3, 1);
        auto btnPay = newtButton(-1, -1, "Bank Card Pay");
        auto btnCancel = newtButton(-1, -1, "Cancel");
        newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnPay, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnCancel, 1, 0, 1, 0, 0, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Bank Card Payment");
        newtGridFree(grid, 1);
        
        bool complete = 0;
        
        do {
            auto answer = newtRunForm(form);
            
            if (answer == btnCancel) {
                complete = true;
            } else if (answer == btnPay) {
                complete = payBank(data);
            }
        } while (!complete);
        
        newtFormDestroy(form);
        newtPopWindow();
    }
    
    static void showGiftCard(PaymentProperties& pp)
    {
        const char *input_cardid, *input_payamount;
        
        auto grid = newtCreateGrid(1, 2);
        
        auto amountGrid = newtCreateGrid(2, 4);
        auto lblNeedPay = newtLabel(-1, -1, "Need pay:");
        auto txtNeedPay = newtTextbox(-1, -1, 20, 1, 0);
        newtTextboxSetText(txtNeedPay, Utils::to_string_with_precision((float)(pp.total100 - pp.complete100) / 100, 2).c_str());
        auto lblPayAmount = newtLabel(-1, -1, "Pay amount:");
        auto entryPayAmount = newtEntry(-1, -1, Utils::to_string_with_precision((float)(pp.total100 - pp.complete100) / 100, 2).c_str(), 20, &input_payamount, 0);
        auto lblCardId = newtLabel(-1, -1, "Gift card ID:");
        auto entryCardId = newtEntry(-1, -1, NULL, 20, &input_cardid, 0);
        auto lblCardBalance = newtLabel(-1, -1, "Gift card Balance:");
        auto txtCardBalance = newtTextbox(-1, -1, 20, 1, 0);
        
        newtGridSetField(amountGrid, 0, 0, NEWT_GRID_COMPONENT, lblNeedPay, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 0, NEWT_GRID_COMPONENT, txtNeedPay, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 1, NEWT_GRID_COMPONENT, lblPayAmount, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 1, NEWT_GRID_COMPONENT, entryPayAmount, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 2, NEWT_GRID_COMPONENT, lblCardId, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 2, NEWT_GRID_COMPONENT, entryCardId, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 3, NEWT_GRID_COMPONENT, lblCardBalance, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 3, NEWT_GRID_COMPONENT, txtCardBalance, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 0, NEWT_GRID_SUBGRID, amountGrid, 0, 0, 0, 0, 0, 0);
        
        EntryGiftCardPayAmountCallbackData data = {pp, entryPayAmount, entryCardId, txtCardBalance};
        newtComponentAddCallback(entryCardId, entryGiftCardIdCallback, &data);
        
        auto buttonGrid = newtCreateGrid(3, 1);
        auto btnPay = newtButton(-1, -1, "Gift Card Pay");
        auto btnCancel = newtButton(-1, -1, "Cancel");
        newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnPay, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnCancel, 1, 0, 1, 0, 0, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Gift Card Payment");
        newtGridFree(grid, 1);
        
        bool complete = 0;
        
        do {
            auto answer = newtRunForm(form);
            
            if (answer == btnCancel) {
                complete = true;
            } else if (answer == btnPay) {
                complete = payGift(data);
            }
        } while (!complete);
        
        newtFormDestroy(form);
        newtPopWindow();
    }
    
    static bool execute(Basket& b)
    {
        auto grid = newtCreateGrid(1, 2);
        
        auto amountGrid = newtCreateGrid(2, 2);
        auto lblNeedPay = newtLabel(-1, -1, "Need pay:");
        auto txtNeedPay = newtTextbox(-1, -1, 20, 1, 0);
        auto lblTotal = newtLabel(-1, -1, "Total:");
        auto txtTotal = newtTextbox(-1, -1, 20, 1, 0);
        newtGridSetField(amountGrid, 0, 0, NEWT_GRID_COMPONENT, lblNeedPay, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 0, NEWT_GRID_COMPONENT, txtNeedPay, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 0, 1, NEWT_GRID_COMPONENT, lblTotal, 0, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(amountGrid, 1, 1, NEWT_GRID_COMPONENT, txtTotal, 1, 0, 0, 0, NEWT_ANCHOR_LEFT, 0);
        newtGridSetField(grid, 0, 0, NEWT_GRID_SUBGRID, amountGrid, 0, 0, 0, 0, 0, 0);
        
        auto buttonGrid = newtCreateGrid(3, 1);
        auto btnCash = newtButton(-1, -1, "Cash");
        auto btnBankCard = newtButton(-1, -1, "Bank Card");
        auto btnGiftCard = newtButton(-1, -1, "Gift Card");
        newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnCash, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnBankCard, 1, 0, 1, 0, 0, 0);
        newtGridSetField(buttonGrid, 2, 0, NEWT_GRID_COMPONENT, btnGiftCard, 1, 0, 1, 0, 0, 0);
        newtGridSetField(grid, 0, 1, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
        
        auto form = newtForm(NULL, NULL, 0);
        newtGridAddComponentsToForm(grid, form, 1);
        
        newtGridWrappedWindow(grid, (char*)"Payment");
        newtGridFree(grid, 1);
        
        unsigned int price = (float)b.getTotalPrice100() / 100 * 100;
        PaymentProperties pp = { price, 0 };
        
        do {
            newtTextboxSetText(txtNeedPay, ("RMB " + Utils::to_string_with_precision((float)(pp.total100 - pp.complete100) / 100, 2)).c_str());
            newtTextboxSetText(txtTotal, ("RMB " + Utils::to_string_with_precision((float)pp.total100 / 100, 2)).c_str());
            
            auto answer = newtRunForm(form);
            
            if (answer == btnCash) {
                showCash(pp);
            } else if (answer == btnBankCard) {
                showBankCard(pp);
            } else if (answer == btnGiftCard) {
                showGiftCard(pp);
            }
        } while (pp.complete100 < pp.total100);
        
        newtFormDestroy(form);
        newtPopWindow();
        
        FormPaymentComplete::show(b);
        
        return true;
    }
};

#endif
