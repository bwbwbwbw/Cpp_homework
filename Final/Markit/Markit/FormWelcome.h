//
//  FormWelcome.h
//  Markit
//
//  Created by Breezewish on 4/26/14.
//  Copyright (c) 2014 Breezewish. All rights reserved.
//

#ifndef Markit_FormWelcome_h
#define Markit_FormWelcome_h

#include "FormUtils.h"
#include "FormCheckout.h"
#include "FormSave.h"

class FormWelcome
{
public:
    static void show()
    {
        while (true) {
            newtCls();
            
            auto grid = newtCreateGrid(1, 2);
            
            auto txtWelcome = newtTextbox(-1, -1, 49, 2, NULL);
            newtTextboxSetText(txtWelcome, "Welcome to Markit by Breezewish :-)"
                               "\n/* Use arrow keys to move and ENTER to select. */");
            newtGridSetField(grid, 0, 0, NEWT_GRID_COMPONENT, txtWelcome, 2, 1, 2, 0, 0, 0);
            
            auto buttonGrid = newtCreateGrid(3, 1);
            auto btnCheckout = newtButton(-1, -1, "Check Out");
            auto btnSave = newtButton(-1, -1, "Save");
            auto btnQuit = newtButton(-1, -1, "Quit");
            newtGridSetField(buttonGrid, 0, 0, NEWT_GRID_COMPONENT, btnCheckout, 1, 0, 1, 0, 0, 0);
            newtGridSetField(buttonGrid, 1, 0, NEWT_GRID_COMPONENT, btnSave, 1, 0, 1, 0, 0, 0);
            newtGridSetField(buttonGrid, 2, 0, NEWT_GRID_COMPONENT, btnQuit, 1, 0, 1, 0, 0, 0);
            newtGridSetField(grid, 0, 1, NEWT_GRID_SUBGRID, buttonGrid, 0, 1, 0, 0, 0, 0);
            
            auto form = newtForm(NULL, NULL, 0);
            newtGridAddComponentsToForm(grid, form, 1);
            
            newtGridWrappedWindow(grid, "Markit");
            newtGridFree(grid, 1);
            
            auto answer = newtRunForm(form);
            
            newtFormDestroy(form);
            newtPopWindow();
            
            if (answer == btnCheckout) {
                FormCheckout::show();
            } else if (answer == btnSave) {
                FormSave::execute();
            } else if (answer == btnQuit) {
                return;
            }
            
            /*
            newtCenteredWindow(50, 10, "Markit");
            
            auto list = newtListbox(18, 3, 5, NEWT_FLAG_RETURNEXIT);
            newtListboxAppendEntry(list, "Check Out", &LISTITEM_CHECKOUT);
            newtListboxAppendEntry(list, "Save Database", &LISTITEM_SAVE);
            newtListboxAppendEntry(list, "Quit", &LISTITEM_QUIT);
            newtListboxSetWidth(list, (25 - 18)*2);
            
            auto form = newtForm(NULL, NULL, 0);
            newtFormAddComponent(form, list);
            newtRunForm(form);
            
            int* u = (int*)newtListboxGetCurrent(list);
            newtFormDestroy(form);
            newtPopWindow();
            
            switch (*u)
            {
                case LISTITEM_CHECKOUT:
                    FormCheckout::show();
                    break;
                case LISTITEM_SAVE:
                    FormSave::execute();
                    break;
                case LISTITEM_QUIT:
                    return;
                    break;
            }*/
        }
    }
};

#endif
