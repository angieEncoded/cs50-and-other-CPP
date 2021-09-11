#include <cs50.h>
#include <stdio.h>


int main(void)
{
    const int x = get_int("Enter an integer: ");
    const int y = get_int("Enter a second integer: ");


    // We would use a float for this one because we can have fractions
    // dividing ints by each other will return int by definition. The resulting value will be truncated.
    const float z = (float)x / (float)y;
    // We can explicitly cast to a float before doing the math

    // Math has already been done on the right hand side, but it's too late to put it in a float

    // Remember to change the placeholder to f
    printf("The sum is %f\n", z);

}