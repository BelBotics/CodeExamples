#include "c_tasks.h"
#include <stdio.h>
#include "string.h"

char firstNonRepeatingChar(char * string)
{
    int length = strlen(string);
    int j = 0;

    for (int i = 0; i < length; i++)
    {
        char tempChar = *(string + i);
        for(j = 0; j < length; j++)
        {
            if(*(string + j) == tempChar && j != i)
            {
                // this char in not unique
                break;
            }            
        }    
        
        // if we check all characters in the string means that this is non-repeating char
        if(j == length)
        {
            
            return *(string + i);
        }
    }

    // return null string since there is no non-repeating string
    return '\0';
}