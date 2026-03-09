#pragma once
#include <ncurses.h>
#include "excercise.hpp"


#define MAIN_MENU_OFFSET_Y 3
#define MENU_ITEMS_PER_PAGE 20

// forward declaration of menu item structure
struct MenuItem
{
    int value;
    // pointer to excercise base class for more complex exercises that require state or multiple steps
    EcxerciseBase* excercise = nullptr;
    const char* label;
    // function pointer for the action to execute when this menu item is selected
    void (*action)() = nullptr;
};

extern const MenuItem MENU_ITEMS[];

void ncurses_init();
int ncurses_menuSelect(int &selectedIndex, int &pageIndex);
void ncurses_displayMenu(int selectedIndex, int pageIndex);
void ncurses_prepareOutput();
void ncurses_outputClear();
