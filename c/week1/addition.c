#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // const int x = get_int("Enter an integer: ");
    // const int y = get_int("Enter a second integer: ");
    const long y = get_long("Enter an integer: ");
    const long x = get_long("Enter a second integer: ");

    printf("The sum is %li\n", x + y);



}