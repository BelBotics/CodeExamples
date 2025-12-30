#include "reverse_string.h"

void outputRevString(char string[], int len)
{
    printf("\nInput string was %s: ", string);

    for(int i = len - 1 ; i >= 0; i--)
    {
        putchar((char)*(string + i));
    }
}