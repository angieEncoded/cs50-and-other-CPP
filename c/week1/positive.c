#include <stdio.h>
#include <cs50.h>

// My prototypes
int get_positive_int(void);


int main (void)
{
    int i = get_positive_int();
    printf("%i\n", i);
}

// Prompts user for a positive integer
int get_positive_int(void)
{
    // In this case we can't declare the variable in the block. It will be out of scope when we go to check it or return it
    int n;
    do
    {
    // Call this item from the cs50 library
       n = get_int("Positive Integer: ");
    }
    // Do this loop again if the integer is not positive
    while(n < 1);
    return n;
}