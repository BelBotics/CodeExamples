#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <memory>

#include <ncurses.h>
// include ncurses library (support common include paths)
// #if __has_include(<ncurses/ncurses.h>)
// #include <ncurses/ncurses.h>
// #elif __has_include(<ncurses.h>)
// #include <ncurses.h>
// #else
// #error "ncurses headers not found. Install ncurses development package."
// #endif

void ncurses_init()
{
    initscr(); // initialize ncurses
    cbreak(); // disable line buffering
    //noecho(); // disable echoing of input characters
    curs_set(0); // hide the cursor
    keypad(stdscr, TRUE); // enable special keys (e.g., arrow keys)

    // set blue background like menuconfig
    if(has_colors())
    {
        start_color();
        use_default_colors();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        bkgd(COLOR_PAIR(1));
        clear();
        refresh();
    }
}

// input array
std::vector<int> nums = {2, 4, 8, 9, 11};
// target value
int target = 17;

class Button
{
    public:
    // define enum for button states
    enum class buttonState
    {
        IDLE = 0,
        PRESSED, 
        HELD, 
    };

    void update(uint8_t pressed, uint32_t dt_ms)
    {
        switch(state)
        {
            case buttonState::IDLE:
            {
                // if button is pressed, transition to PRESSED state
                if(pressed)
                {
                    state = buttonState::PRESSED;
                    held_ms = 0; // reset held time
                    std::cout << "Button is PRESSED" << std::endl;
                }else
                {
                    std::cout << "Button is IDLE" << std::endl;            
                }
                break;
            }
            case buttonState::PRESSED:
            {
                if(pressed)
                {
                    held_ms += dt_ms; // accumulate held time
                    if(held_ms >= heldThreshold_ms)
                    {
                        state = buttonState::HELD; // transition to HELD state
                        std::cout << "Button is now HELD" << std::endl;
                    }else
                    {
                        std::cout << "Button is still PRESSED, held time: " << held_ms << " ms" << std::endl;
                    }

                }else
                {
                    state = buttonState::IDLE;
                    std::cout << "Button is RELEASED" << std::endl;
                    break;    
                }
                break;    
            }
            case buttonState::HELD:
            {
                if(!pressed)
                {
                    state = buttonState::IDLE;
                    std::cout << "Button is released from held state" << std::endl;
                    break;    
                }
                std::cout << "Button is held" << std::endl;
                break;    
            }   
            default:
            {
                std::cout << "Invalid button state" << std::endl;
                break;    
            }                      
        }
    }

    private:
        buttonState state;
        uint32_t held_ms;
        const uint32_t heldThreshold_ms = 800; // 800 ms threshold for held state
};





std::pair<int, int> twoSum(std::vector<int>& nums, int& target)
{
    // in vector nums, find two numbers that add to target and return their indices
    for(auto it = nums.begin(); it != nums.end(); ++it)
    {
        // calculate needed value by subracting current value from target
        int neededValue = target - *it;
        // check if needed value is in vector 
        if(std::find(nums.begin(), nums.end(), neededValue) != nums.end())
        {
            std::cout << "Found two numbers that add to target (" << target << "): " << *it << " and " << neededValue << std::endl;
            // return indices of the two numbers
            int index1 = it - nums.begin();
            int index2 = std::find(nums.begin(), nums.end(), neededValue) - nums.begin();
            return std::make_pair(index1, index2);
        }   
    }
    
    // code for task 1 goes here
    std::cout << "No two numbers add to target" << std::endl;
    return std::make_pair(0, 0);
}

// check if a number is a power of two by comparing the number with its bitwise AND with the numer minus one.
bool isPowerOfTwo(int num)
{
    // check if num is greater than 0
    if(num > 0)
    {
        // check if num is a power of two by using bitwise AND operator to check if num has only one bit set
        return (num & (num - 1)) == 0;
    }
    return false;
}
// task 12 swap endianess of a 32-bit integer
void swapEndianess(uint32_t& num)
{
    uint32_t tempValue;

    tempValue = (num >> 24) & 0x000000FF;
    tempValue |= (num >> 8) & 0x0000FF00;
    tempValue |= (num << 8) & 0x00FF0000;
    tempValue |= (num << 24) & 0xFF000000;
    num = tempValue;
}

// task 10 count set bits in a 32-bit integer
uint8_t countSetBits(uint32_t num)
{
    int count = 0;
    while(num)
    {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

// return value from any particular address in memory
int readValueFromAddress(uint64_t address)
{

    std::cout << "Attempting to read value from address: 0x" << std::hex << address << std::dec << std::endl;
    // cast an address to a pointer
    int* ptr = (int*)address;

    // return the value at the address
    return *ptr;
}

// display virtual address space range for the current process by parsing /proc/self/maps
void getAddressRange()
{
    std::ifstream mapsFile("/proc/self/maps");
    if(!mapsFile)
    {
        std::cout << "Unable to open /proc/self/maps" << std::endl;
        return;
    }

    uint64_t minAddr = std::numeric_limits<uint64_t>::max();
    uint64_t maxAddr = 0;

    std::string line;
    while(std::getline(mapsFile, line))
    {
        std::cout << line << std::endl;
        std::istringstream iss(line);
        std::string range;
        if(!(iss >> range))
        {
            continue;
        }

        auto dashPos = range.find('-');
        if(dashPos == std::string::npos)
        {
            continue;
        }

        std::string startStr = range.substr(0, dashPos);
        std::string endStr = range.substr(dashPos + 1);

        uint64_t start = 0;
        uint64_t end = 0;
        std::istringstream startStream(startStr);
        std::istringstream endStream(endStr);
        startStream >> std::hex >> start;
        endStream >> std::hex >> end;

        if(start < minAddr)
        {
            minAddr = start;
        }
        if(end > maxAddr)
        {
            maxAddr = end;
        }
    }

    if(minAddr == std::numeric_limits<uint64_t>::max())
    {
        std::cout << "No address ranges found." << std::endl;
        return;
    }

    std::cout << "Virtual address space range: 0x" << std::hex << minAddr
              << " - 0x" << maxAddr << std::dec << std::endl;
}

struct MenuItem
{
    int value;
    const char* label;
};

static const MenuItem MENU_ITEMS[] = {
    {1, "1. Task 1: Option 1"},
    {2, "2. Task 2: Option 2"},
    {3, "3. Task 3: Option 3"},
    {4, "4. Return indices of two numbers that add to target."},
    {5, "5. Task 5: Option 5"},
    {6, "6. Task 6: Option 6"},
    {7, "7. Task 7: Option 7"},
    {8, "8. Task 8: Option 8"},
    {9, "9. Task 9: Option 9"},
    {10, "10. Count set bits"},
    {11, "11. Check power of two"},
    {12, "12. Swap endianess of a 32-bit integer"},
    {13, "13. Task 13: Option 13"},
    {14, "14. Task 14: Option 14"},
    {15, "15. Task 15: Option 15"},
    {16, "16. Task 16: Option 16"},
    {17, "17. Task 17: Option 17"},
    {18, "18. Task 18: Option 18"},
    {34, "34. Simple button state machine"},
    {51, "51. Read value from memory address"},
    {52, "52. Show process address space range"},
    {53, "53. Random integer number generator"}
};

void ncurses_displayMenu(int selectedIndex)
{
    clear(); // clear the screen
    const int menuCount = static_cast<int>(sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]));

    for(int i = 0; i < menuCount; ++i)
    {
        if(i == selectedIndex)
        {
            // turn on reverse attribute for the selected item
            attron(A_REVERSE);
        }
        mvprintw(i, 0, "%s", MENU_ITEMS[i].label);
        if(i == selectedIndex)
        {
            // turn off reverse attribute after printing the selected item
            attroff(A_REVERSE);
        }
    }

    mvprintw(menuCount + 1, 0, "Use \u2191/\u2193 to move, Enter to select.");
    refresh(); // refresh the screen to show changes
}

int ncurses_menuSelect(int& selectedIndex)
{
    const int menuCount = static_cast<int>(sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]));
    int ch = 0;

    while(true)
    {
        ncurses_displayMenu(selectedIndex);
        ch = getch();

        if(ch == KEY_UP)
        {
            selectedIndex = (selectedIndex - 1 + menuCount) % menuCount;
        }
        else if(ch == KEY_DOWN)
        {
            selectedIndex = (selectedIndex + 1) % menuCount;
        }
        else if(ch == '\n' || ch == '\r')
        {
            return MENU_ITEMS[selectedIndex].value;
        }
    }
}

int main()
{
    ncurses_init();

    int selection;
    int selectedIndex = 0;

    // generate switch statement for the selection
    while(1)
    {
        selection = ncurses_menuSelect(selectedIndex);
        switch(selection)
        {
            case 1:
            {
                // clear the screen and display the selected option
                clear();
                mvprintw(0, 0, "You selected option 1");
                refresh();
                break;
            }
            case 2:
                clear();
                mvprintw(0, 0, "You selected option 2");
                refresh();
                break;
            case 3:
                clear();
                mvprintw(0, 0, "You selected option 3");
                refresh();
                break;
            case 4:
            {
                clear();
                mvprintw(0, 0, "You selected option 4");
                refresh();
                auto tempPair = twoSum(nums, target);
                mvprintw(1, 0, "Indices are: %d and %d", tempPair.first, tempPair.second);
                refresh();
                break;
            }            
            case 5:
                clear();
                mvprintw(0, 0, "You selected option 5");
                refresh();
                break;
            case 6:
                clear();
                mvprintw(0, 0, "You selected option 6");
                refresh();
                break;
            case 7:
                clear();
                mvprintw(0, 0, "You selected option 7");
                refresh();
                break;
            case 8:                                             
                clear();
                mvprintw(0, 0, "You selected option 8");
                refresh();
                break;
            case 9:
                clear();
                mvprintw(0, 0, "You selected option 9");
                refresh();
                break;
            case 10:
            {
                clear();
                mvprintw(0, 0, "You selected option 10");
                refresh();
                mvprintw(1, 0, "Enter a 32-bit integer value: ");
                refresh();
                uint32_t num;
                std::cin >> num;
                uint8_t setBits = countSetBits(num);
                mvprintw(2, 0, "Number of set bits in %u (%s) is: %d bits", num, std::bitset<sizeof(uint32_t) * 8>(num).to_string().c_str(), static_cast<int>(setBits));
                refresh();
                break;
            }
            case 11:
            {
                clear();
                mvprintw(0, 0, "You selected option 11");
                refresh();
                mvprintw(1, 0, "Enter a number to check if it is a power of two: ");
                refresh();
                int num;
                std::cin >> num;
                if(isPowerOfTwo(num))
                {
                    mvprintw(2, 0, "%d is a power of two.", num);
                    refresh();
                }else
                {
                    mvprintw(2, 0, "%d is not a power of two.", num);
                    refresh();
                }
                break;
            }
            case 12:
            {
                clear();
                mvprintw(0, 0, "You selected option 12");
                refresh();
                uint32_t num;
                mvprintw(1, 0, "Enter a 32-bit integer: ");
                refresh();
                std::cin >> num;
                swapEndianess(num);
                mvprintw(2, 0, "Swapped endianess: %u", num);
                refresh();
                break;
            }
            case 13:
                clear();
                mvprintw(0, 0, "You selected option 13");
                refresh();
                break;
            case 14:
                clear();
                mvprintw(0, 0, "You selected option 14");
                refresh();
                break;
            case 15:
                clear();
                mvprintw(0, 0, "You selected option 15");
                refresh();
                break;
            case 16:
                clear();
                mvprintw(0, 0, "You selected option 16");
                refresh();
                break;
            case 17:
                clear();
                mvprintw(0, 0, "You selected option 17");
                refresh();
                break;
            case 18:
                clear();
                mvprintw(0, 0, "You selected option 18");
                refresh();
                break;
            case 34:
            {
                std::unique_ptr<Button> button1 = std::make_unique<Button>();
                clear();
                mvprintw(0, 0, "You selected option 34");
                refresh();
                    // Simulate button input in a loop

                while(true)
                { 
                    mvprintw(1, 0, "Press the button? (1 for yes, 0 for no, 2 to exit): ");
                    refresh();
                    int pressed;
                    std::cin >> pressed;
                    mvprintw(2, 0, "You entered: %d", static_cast<int>(pressed));
                    refresh();
                    if(pressed == 2)
                    {
                        break;
                    }
                    // Update button state with a fixed time step (e.g., 100 ms)
                    button1->update(pressed, 100);
                }
                break;
            }
            case 51:
            {        
                clear();
                mvprintw(0, 0, "You selected option 51");
                refresh();
                mvprintw(1, 0, "Enter a memory address in hexadecimal: ");
                refresh();
                mvprintw(2, 0, "Next action will likely cause a crash if the address is outside of the process memory space or if the address is not properly aligned.");
                refresh();
                uint64_t address;
                std::cin >> std::hex >> address;
                int value = readValueFromAddress(address);
                mvprintw(3, 0, "Value at address 0x%llx: %d", address, value);
                refresh();
                break;
            }
            case 52:
            {
                clear();
                mvprintw(0, 0, "You selected option 52");
                refresh();
                getAddressRange();
                break;
            }
            case 53:
            {
                int minValue, maxValue;
                clear();
                mvprintw(0, 0, "You selected option 53");
                refresh();
                mvprintw(1, 0, "Random integer number generator");
                refresh();
                mvprintw(2, 0, "Enter minimum and maximum values (separated by space): ");
                refresh();
                std::cin >> minValue >> maxValue;
                if(minValue > maxValue)
                {
                    std::swap(minValue, maxValue);
                }

                int randomValue = minValue + std::rand() % (maxValue - minValue + 1);
                mvprintw(3, 0, "Generated random integer between %d and %d: %d", minValue, maxValue, randomValue);
                refresh();

                break;
            }
            default:
                mvprintw(0, 0, "Invalid selection");
                refresh();
                break;          
        }
    
        // wait for user input before showing the menu again
        mvprintw(23, 0, "Press Enter to return to the menu...");
        refresh();
        int ch = 0;
        while(ch != '\n' && ch != '\r')
        {
            ch = getch();
        }
    }

    return 0;
}