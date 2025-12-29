#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "reverse_string.h"

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

    // Add new line
    printf("\n");

    exit(0);
}