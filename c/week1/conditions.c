#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // promt user for the values we want
    const int x = get_int("x: ");
    const int y = get_int("y: ");

    // compare the values
    if (x > y)
    {
        // Send feedback to the user
        printf("x(%i) is greater than y(%i)\n", x, y);
    }
    else if (x < y)
    {
        // Send feedback to the user
        printf("x(%i)is less than y(%i)\n", x, y);
    }
    else
    {
        // Send feedback to the user
        printf("x(%i) and y(%i) are equal\n", x, y);
    }


}