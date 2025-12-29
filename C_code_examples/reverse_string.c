#include "reverse_string.h"

void outputRevString(char string[], int len)
{
    printf("Input string was %string:", string);

    for(int i = len - 1 ; i >= 0; i--)
    {
        putchar((char)*(string + i));
    }
}