#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// Write a function that takes in three inputs and determines if it can make a triangle


// prototypes
bool isTriangle(int sidea, int sideb, int sidec);

int main()
{

    const bool results = isTriangle(14, 13, 15);

    // If it gets a falsy value it will do the second thing
    printf("%s\n", results ? "True" : "False");

}


bool isTriangle(int sidea, int sideb, int sidec)
{

    // Be sure they are all positive integers
    if (sidea < 1 || sideb < 1 || sidec < 1)
    {
        return false;
    }

    // Check that any two sides can be greater than the other side
    if (!(sidea + sideb > sidec) || !(sideb + sidec > sidea) || !(sidea + sidec > sideb))
    {
        return false;
    }

    return true;

}