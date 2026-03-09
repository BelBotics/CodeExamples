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
#include "display.hpp"

// global variables for menu selection
extern WINDOW* menuWin;
extern WINDOW* outputWin;

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


int main()
{
    // initialize ncurses library and set up the terminal
    ncurses_init();

    int selection;
    int selectedIndex = 0;
    int pageIndex = 0;

    // generate switch statement for the selection
    while(1)
    {
        selection = ncurses_menuSelect(selectedIndex, pageIndex);
        ncurses_prepareOutput();
        switch(selection)
        {
            case 1:
            {
                // clear the output window and display the selected option
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 1");
                wrefresh(outputWin);
                break;
            }
            case 2:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 2");
                wrefresh(outputWin);
                break;
            case 3:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 3");
                wrefresh(outputWin);
                break;
            case 4:
            {
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 4");
                wrefresh(outputWin);
                if(MENU_ITEMS[selectedIndex].action)
                {
                    MENU_ITEMS[selectedIndex].action();
                }
                auto tempPair = MENU_ITEMS[selectedIndex].excercise->action();
                
                mvwprintw(outputWin, 1, 0, "Indices are: %d and %d", tempPair.first, tempPair.second);
                wrefresh(outputWin);
                break;
            }            
            case 5:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 5");
                wrefresh(outputWin);
                break;
            case 6:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 6");
                wrefresh(outputWin);
                break;
            case 7:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 7");
                wrefresh(outputWin);
                break;
            case 8:                                             
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 8");
                wrefresh(outputWin);
                break;
            case 9:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 9");
                wrefresh(outputWin);
                break;
            case 10:
            {
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 10");
                wrefresh(outputWin);
                mvwprintw(outputWin, 1, 0, "Enter a 32-bit integer value: ");
                wrefresh(outputWin);
                uint32_t num;
                std::cin >> num;
                uint8_t setBits = countSetBits(num);
                mvwprintw(outputWin, 2, 0, "Number of set bits in %u (%s) is: %d bits", num, std::bitset<sizeof(uint32_t) * 8>(num).to_string().c_str(), static_cast<int>(setBits));
                wrefresh(outputWin);
                break;
            }
            case 11:
            {
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 11");
                wrefresh(outputWin);
                mvwprintw(outputWin, 1, 0, "Enter a number to check if it is a power of two: ");
                wrefresh(outputWin);
                int num;
                std::cin >> num;
                if(isPowerOfTwo(num))
                {
                    mvwprintw(outputWin, 2, 0, "%d is a power of two.", num);
                    wrefresh(outputWin);
                }else
                {
                    mvwprintw(outputWin, 2, 0, "%d is not a power of two.", num);
                    wrefresh(outputWin);
                }
                break;
            }
            case 12:
            {
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 12");
                wrefresh(outputWin);
                uint32_t num;
                mvwprintw(outputWin, 1, 0, "Enter a 32-bit integer: ");
                wrefresh(outputWin);
                std::cin >> num;
                swapEndianess(num);
                mvwprintw(outputWin, 2, 0, "Swapped endianess: %u", num);
                wrefresh(outputWin);
                break;
            }
            case 13:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 13");
                wrefresh(outputWin);
                break;
            case 14:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 14");
                wrefresh(outputWin);
                break;
            case 15:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 15");
                wrefresh(outputWin);
                break;
            case 16:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 16");
                wrefresh(outputWin);
                break;
            case 17:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 17");
                wrefresh(outputWin);
                break;
            case 18:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 18");
                wrefresh(outputWin);
                break;
            case 19:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 19");
                wrefresh(outputWin);
                break;
            case 20:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 20");
                wrefresh(outputWin);
                break;
            case 21:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 21");
                wrefresh(outputWin);
                break;
            case 22:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 22");
                wrefresh(outputWin);
                break;
            case 23:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 23");
                wrefresh(outputWin);
                break;
            case 24:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 24");
                wrefresh(outputWin);
                break;
            case 25:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 25");
                wrefresh(outputWin);
                break;
            case 26:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 26");
                wrefresh(outputWin);
                break;
            case 27:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 27");       
                wrefresh(outputWin);
                break;  
            case 28:
                ncurses_outputClear();    
                mvwprintw(outputWin, 0, 0, "You selected option 28");
                wrefresh(outputWin);
                break;
            case 29:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 29");
                wrefresh(outputWin);
                break;
            case 30:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 30");
                wrefresh(outputWin);
                break;
            case 31:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 31");
                wrefresh(outputWin);
                break;
            case 32:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 32");
                wrefresh(outputWin);
                break;
            case 33:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 33");
                wrefresh(outputWin);
                break;  
            case 34:
            {
                std::unique_ptr<Button> button1 = std::make_unique<Button>();
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 34");
                wrefresh(outputWin);
                    // Simulate button input in a loop

                while(true)
                { 
                    mvwprintw(outputWin, 1, 0, "Press the button? (1 for yes, 0 for no, 2 to exit): ");
                    wrefresh(outputWin);
                    int pressed;
                    std::cin >> pressed;
                    mvwprintw(outputWin, 2, 0, "You entered: %d", static_cast<int>(pressed));
                    wrefresh(outputWin);
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
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 51");
                wrefresh(outputWin);
                mvwprintw(outputWin, 1, 0, "Enter a memory address in hexadecimal: ");
                wrefresh(outputWin);
                mvwprintw(outputWin, 2, 0, "Next action will likely cause a crash if the address is outside of the process memory space or if the address is not properly aligned.");
                wrefresh(outputWin);
                uint64_t address;
                std::cin >> std::hex >> address;
                int value = readValueFromAddress(address);
                mvwprintw(outputWin, 3, 0, "Value at address 0x%llx: %d", address, value);
                wrefresh(outputWin);
                break;
            }
            case 52:
            {
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 52");
                wrefresh(outputWin);
                getAddressRange();
                break;
            }
            case 53:
            {
                int minValue, maxValue;
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "You selected option 53");
                wrefresh(outputWin);
                mvwprintw(outputWin, 1, 0, "Random integer number generator");
                wrefresh(outputWin);
                mvwprintw(outputWin, 2, 0, "Enter minimum and maximum values (separated by space): ");
                wrefresh(outputWin);
                std::cin >> minValue >> maxValue;
                if(minValue > maxValue)
                {
                    std::swap(minValue, maxValue);
                }

                int randomValue = minValue + std::rand() % (maxValue - minValue + 1);
                mvwprintw(outputWin, 3, 0, "Generated random integer between %d and %d: %d", minValue, maxValue, randomValue);
                wrefresh(outputWin);

                break;
            }
            default:
                ncurses_outputClear();
                mvwprintw(outputWin, 0, 0, "Invalid selection");
                wrefresh(outputWin);
                break;          
        }
    
        // wait for user input before showing the menu again
        mvwprintw(outputWin, 23, 0, "Press Enter to return to the menu...");
        wrefresh(outputWin);
        int ch = 0;
        while(ch != '\n' && ch != '\r')
        {
            ch = getch();
        }
    }

    return 0;
}