#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

// input array
std::vector<int> nums = {2, 4, 8, 9, 11};
// target value
int target = 17;

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

int main()
{
    // choose a selection from the menu
    std::cout << "Please select an option from the menu:" << std::endl;
    std::cout << "1. Task 1: Option 1" << std::endl;
    std::cout << "2. Task 2: Option 2" << std::endl;
    std::cout << "3. Task 3: Option 3" << std::endl;
    std::cout << "4. Return indices of two numbers that add to target." << std::endl;
    std::cout << "5. Task 5: Option 5" << std::endl;
    std::cout << "6. Task 6: Option 6" << std::endl;
    std::cout << "7. Task 7: Option 7" << std::endl;
    std::cout << "8. Task 8: Option 8" << std::endl;
    std::cout << "9. Task 9: Option 9" << std::endl;
    std::cout << "10. Count set bits" << std::endl;
    std::cout << "11. Check power of two" << std::endl;
    std::cout << "12. Swap endianess of a 32-bit integer" << std::endl;
    std::cout << "13. Task 13: Option 13" << std::endl;
    std::cout << "14. Task 14: Option 14" << std::endl;
    std::cout << "15. Task 15: Option 15" << std::endl;
    std::cout << "16. Task 16: Option 16" << std::endl;
    std::cout << "17. Task 17: Option 17" << std::endl;
    std::cout << "18. Task 18: Option 18" << std::endl;



    std::cout << "Enter your selection: ";
    int selection;
    std::cin >> selection;


    // generate switch statement for the selection
    switch(selection)
    {
        case 1:
        {
            std::cout << "You selected option 1" << std::endl;
            break;
        }
        case 2:
            std::cout << "You selected option 2" << std::endl;
            break;
        case 3:
            std::cout << "You selected option 3" << std::endl;
            break;
        case 4:
        {
            auto tempPair = twoSum(nums, target);
            std::cout << "Indices are: " << tempPair.first << " and " << tempPair.second << std::endl;
            break;
        }            
        case 5:
            std::cout << "You selected option 5" << std::endl;
            break;
        case 6:
            std::cout << "You selected option 6" << std::endl;
            break;
        case 7:
            std::cout << "You selected option 7" << std::endl;
            break;
        case 8:                                             
            std::cout << "You selected option 8" << std::endl;
            break;
        case 9:
            std::cout << "You selected option 9" << std::endl;
            break;
        case 10:
        {
            std::cout << "You selected option 10" << std::endl;
            std::cout << "Enter a 32-bit integer value: ";
            uint32_t num;
            std::cin >> num;
            uint8_t setBits = countSetBits(num);
            std::cout << "Number of set bits in " << num <<  " (" << std::bitset<sizeof(uint32_t) * 8>(num) << ") is: " << static_cast<int>(setBits) << " bits" << std::endl;
            break;
        }
        case 11:
        {
            std::cout << "You selected option 11" << std::endl;
            std::cout << "Enter a number to check if it is a power of two: ";
            int num;
            std::cin >> num;
            if(isPowerOfTwo(num))
            {
                std::cout << num << " is a power of two." << std::endl;
            }else
            {
                std::cout << num << " is not a power of two." << std::endl;
            }
            break;
        }
        case 12:
        {
            std::cout << "You selected option 12" << std::endl;
            uint32_t num;
            std::cout << "Enter a 32-bit integer: ";
            std::cin >> num;
            swapEndianess(num);
            std::cout << "Swapped endianess: " << num << std::endl;
            break;
        }
        case 13:
            std::cout << "You selected option 13" << std::endl;
            break;
        case 14:
            std::cout << "You selected option 14" << std::endl;
            break;
        case 15:
            std::cout << "You selected option 15" << std::endl;
            break;
        case 16:
            std::cout << "You selected option 16" << std::endl;
            break;
        case 17:
            std::cout << "You selected option 17" << std::endl;
            break;
        case 18:
            std::cout << "You selected option 18" << std::endl;
            break;
        default:
            std::cout << "Invalid selection" << std::endl;
            break;          
    }

    return 0;
}