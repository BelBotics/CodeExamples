#include "is_power_of_two.h"

char isPowerOfTwo(int num)
{
    // check if last bit is one and number equeal to 1
    while(num >=1)
    {
        if(num == 1)
        {
            return 1;
        }
        else if(num & 1)
        {
            // number is not equal to 1 but LSB is one
            return 0;
        }
        else
        {
            num = num >> 1;
        }
    } 
    return 0;   
}