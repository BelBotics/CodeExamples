#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "reverse_string.h"
#include "is_power_of_two.h"
#include "c_tasks.h"

int main(int argc, char *argv[])
{
    // input argument is string that shall be written in reverse order
    if(argc < 2)
    {
        printf("Wrong number of input parameters, at least one required\n");
        exit(1);
    }

    // size of a string
    int str_size = strlen(argv[1]);

    outputRevString(argv[1], str_size);

    /* Task 2: return first non-repeating character */
    printf("\nFirst non-repeating char is: %c\n", firstNonRepeatingChar(argv[1]));

   
    int num;
    printf("\nEnter number up to which to calculate if power of two:\n");
    
    scanf("%d", &num);
    
    // write all number which are power of two intil some bih number e.g. 1025
    for(int i = 0; i <= num; i++)
    {
        if(isPowerOfTwo(i)) printf("\nThe number %d is not power of two\n", i);
    }

    // Add new line
    printf("\n");

    exit(0);
}