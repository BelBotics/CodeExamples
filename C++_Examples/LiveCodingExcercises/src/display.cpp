#include <algorithm>
#include "display.hpp"

// global variables for menu selection
WINDOW* menuWin;
WINDOW* outputWin;

// reference to an global object of the SumTwoNumbers class to be used in the menu
extern SumTwoNumbers sumTwoNumbersExercise;

const MenuItem MENU_ITEMS[] = {
    {1, nullptr, "  | 1. Task 1: Option 1                                                                          |", nullptr},
    {2, nullptr, "  | 2. Task 2: Option 2                                                                          |", nullptr},
    {3, nullptr, "  | 3. Task 3: Option 3                                                                          |", nullptr},    
    {4, &sumTwoNumbersExercise, "  | 4. Return indices of two numbers that add to target.                                         |", nullptr},
    {5, nullptr, "  | 5. Task 5: Option 5                                                                          |", nullptr},
    {6, nullptr, "  | 6. Task 6: Option 6                                                                          |", nullptr},
    {7, nullptr, "  | 7. Task 7: Option 7                                                                          |", nullptr},
    {8, nullptr, "  | 8. Task 8: Option 8                                                                          |", nullptr},
    {9, nullptr, "  | 9. Task 9: Option 9                                                                          |", nullptr},
    {10, nullptr, "  | 10. Count set bits                                                                           |", nullptr},
    {11, nullptr, "  | 11. Check power of two                                                                       |", nullptr},
    {12, nullptr, "  | 12. Swap endianess of a 32-bit integer                                                       |", nullptr},
    {13, nullptr, "  | 13. Task 13: Option 13                                                                       |", nullptr},
    {14, nullptr, "  | 14. Task 14: Option 14                                                                       |", nullptr},
    {15, nullptr, "  | 15. Task 15: Option 15                                                                       |", nullptr},
    {16, nullptr, "  | 16. Task 16: Option 16                                                                       |", nullptr},
    {17, nullptr, "  | 17. Task 17: Option 17                                                                       |", nullptr},
    {18, nullptr, "  | 18. Task 18: Option 18                                                                       |", nullptr},
    {19, nullptr, "  | 19. Task 19: Option 19                                                                       |", nullptr},
    {20, nullptr, "  | 20. Task 20: Option 20                                                                       |", nullptr},
    {21, nullptr, "  | 21. Task 21: Option 21                                                                       |", nullptr},
    {22, nullptr, "  | 22. Task 22: Option 22                                                                       |", nullptr},
    {23, nullptr, "  | 23. Task 23: Option 23                                                                       |", nullptr},
    {24, nullptr, "  | 24. Task 24: Option 24                                                                       |", nullptr},
    {25, nullptr, "  | 25. Task 25: Option 25                                                                       |", nullptr},
    {26, nullptr, "  | 26. Task 26: Option 26                                                                       |", nullptr},
    {27, nullptr, "  | 27. Task 27: Option 27                                                                       |", nullptr},
    {28, nullptr, "  | 28. Task 28: Option 28                                                                       |", nullptr},
    {29, nullptr, "  | 29. Task 29: Option 29                                                                       |", nullptr},
    {30, nullptr, "  | 30. Task 30: Option 30                                                                       |", nullptr},
    {31, nullptr, "  | 31. Task 31: Option 31                                                                       |", nullptr},
    {32, nullptr, "  | 32. Task 32: Option 32                                                                       |", nullptr},
    {33, nullptr, "  | 33. Task 33: Option 33                                                                       |", nullptr},
    {34, nullptr, "  | 34. Simple button state machine                                                              |", nullptr},
    {35, nullptr, "  | 35. Task 35: Option 35                                                                       |", nullptr},
    {36, nullptr, "  | 36. Task 36: Option 36                                                                       |", nullptr},
    {37, nullptr, "  | 37. Task 37: Option 37                                                                       |", nullptr},
    {38, nullptr, "  | 38. Task 38: Option 38                                                                       |", nullptr},
    {39, nullptr, "  | 39. Task 39: Option 39                                                                       |", nullptr},
    {40, nullptr, "  | 40. Task 40: Option 40                                                                       |", nullptr},
    {41, nullptr, "  | 41. Task 41: Option 41                                                                       |", nullptr},
    {42, nullptr, "  | 42. Task 42: Option 42                                                                       |", nullptr},
    {43, nullptr, "  | 43. Task 43: Option 43                                                                       |", nullptr},
    {44, nullptr, "  | 44. Task 44: Option 44                                                                       |", nullptr},
    {45, nullptr, "  | 45. Task 45: Option 45                                                                       |", nullptr},
    {46, nullptr, "  | 46. Task 46: Option 46                                                                       |", nullptr},
    {47, nullptr, "  | 47. Task 47: Option 47                                                                       |", nullptr},
    {48, nullptr, "  | 48. Task 48: Option 48                                                                       |", nullptr},
    {49, nullptr, "  | 49. Task 49: Option 49                                                                       |", nullptr},
    {50, nullptr, "  | 50. Task 50: Option 50                                                                       |", nullptr},
    {51, nullptr, "  | 51. Read value from memory address                                                           |", nullptr},
    {52, nullptr, "  | 52. Show process address space range                                                         |", nullptr},
    {53, nullptr, "  | 53. Random integer number generator                                                          |", nullptr}
};

void ncurses_init()
{    
    initscr(); // initialize ncurses
    cbreak(); // disable line buffering
    //noecho(); // disable echoing of input characters
    curs_set(0); // hide the cursor
    keypad(stdscr, TRUE); // enable special keys (e.g., arrow keys)

    // select menu window
    menuWin = newwin(LINES, COLS, 0, 0);
    // set blue background like menuconfig for menu window
    if(has_colors())
    {
        start_color();
        use_default_colors();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        wbkgd(menuWin, COLOR_PAIR(1));
    }

    box(menuWin, 0, 0); // draw a box around the menu window
    wrefresh(menuWin); // refresh the menu window to show the box

    // create output window as new page
    outputWin = newwin(LINES, COLS, 0, 0);
    // set default background for output window
    if(has_colors())
    {
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
        wbkgd(outputWin, COLOR_PAIR(2));
    }
    wrefresh(outputWin); // refresh the output window to show the background

}

int ncurses_menuSelect(int& selectedIndex, int& pageIndex)
{
    const int menuCount = static_cast<int>(sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]));
    const int pageCount = (menuCount + MENU_ITEMS_PER_PAGE - 1) / MENU_ITEMS_PER_PAGE;
    int ch = 0;

    while(true)
    {
        ncurses_displayMenu(selectedIndex, pageIndex);
        ch = getch();

        if(ch == KEY_UP)
        {
            int startIndex = pageIndex * MENU_ITEMS_PER_PAGE;
            int endIndex = std::min(startIndex + MENU_ITEMS_PER_PAGE, menuCount);
            if(selectedIndex <= startIndex)
            {
                selectedIndex = endIndex - 1;
            }
            else
            {
                selectedIndex -= 1;
            }
        }
        else if(ch == KEY_DOWN)
        {
            int startIndex = pageIndex * MENU_ITEMS_PER_PAGE;
            int endIndex = std::min(startIndex + MENU_ITEMS_PER_PAGE, menuCount);
            if(selectedIndex >= endIndex - 1)
            {
                selectedIndex = startIndex;
            }
            else
            {
                selectedIndex += 1;
            }
        }
        else if(ch == KEY_LEFT)
        {
            pageIndex = (pageIndex - 1 + pageCount) % pageCount;
            int startIndex = pageIndex * MENU_ITEMS_PER_PAGE;
            int endIndex = std::min(startIndex + MENU_ITEMS_PER_PAGE, menuCount);
            selectedIndex = startIndex;
            if(selectedIndex >= endIndex)
            {
                selectedIndex = endIndex - 1;
            }
        }
        else if(ch == KEY_RIGHT)
        {
            pageIndex = (pageIndex + 1) % pageCount;
            int startIndex = pageIndex * MENU_ITEMS_PER_PAGE;
            int endIndex = std::min(startIndex + MENU_ITEMS_PER_PAGE, menuCount);
            selectedIndex = startIndex;
            if(selectedIndex >= endIndex)
            {
                selectedIndex = endIndex - 1;
            }
        }
        else if(ch == '\n' || ch == '\r')
        {
            return MENU_ITEMS[selectedIndex].value;
        }
    }
}

void ncurses_displayMenu(int selectedIndex, int pageIndex)
{
    const int menuCount = static_cast<int>(sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]));
    
    const int pageCount = (menuCount + MENU_ITEMS_PER_PAGE - 1) / MENU_ITEMS_PER_PAGE;
    const int startIndex = pageIndex * MENU_ITEMS_PER_PAGE;
    const int endIndex = std::min(startIndex + MENU_ITEMS_PER_PAGE, menuCount);
    const int visibleCount = endIndex - startIndex;

    //select menu window and clear it
    werase(menuWin);
    box(menuWin, 0, 0); // redraw the box around the menu window

    // at the beginning of the menu print basic program info
    mvwprintw(menuWin, 0, 1, "C++17 ncurses menu example - select an option and press Enter to execute. Press Ctrl+C to exit.");
    mvwprintw(menuWin, 1, 1, "---------------------------------------- Main Menu ---------------------------------------------");
    mvwprintw(menuWin, 2, 1, "Page %d/%d", pageIndex + 1, pageCount);

    // print the menu items for the current page
    for(int i = 0; i < visibleCount; ++i)
    {
        int menuIndex = startIndex + i;
        int row = i + MAIN_MENU_OFFSET_Y;
        if(menuIndex == selectedIndex)
        {
            // turn on reverse attribute for the selected item
            wattron(menuWin, A_REVERSE);
        }
        mvwprintw(menuWin, row, 1, "%s", MENU_ITEMS[menuIndex].label);
        if(menuIndex == selectedIndex)
        {
            // turn off reverse attribute after printing the selected item
            wattroff(menuWin, A_REVERSE);
        }
    }

    mvwprintw(menuWin, visibleCount + MAIN_MENU_OFFSET_Y, 1, "-----------------------------------------------------------------------------------------------");

    mvwprintw(menuWin, visibleCount + MAIN_MENU_OFFSET_Y + 1, 1, "Use ");
    waddch(menuWin, ACS_UARROW);
    waddch(menuWin, '/');
    waddch(menuWin, ACS_DARROW);
    wprintw(menuWin, " to move, ");
    waddch(menuWin, ACS_LARROW);
    waddch(menuWin, '/');
    waddch(menuWin, ACS_RARROW);
    wprintw(menuWin, " to change page, Enter to select. Ctrl+C to exit.");

    wrefresh(menuWin); // refresh the menu window to show changes
}

void ncurses_prepareOutput()
{
    // check if menuWin and outputWin are initialized before trying to clear them
    if(menuWin)
    {
        werase(menuWin);
        wrefresh(menuWin);
    }
    ncurses_outputClear();
}

void ncurses_outputClear()
{
    if(outputWin)
    {
        werase(outputWin);
        box(outputWin, 0, 0);
        wrefresh(outputWin);
    }
}