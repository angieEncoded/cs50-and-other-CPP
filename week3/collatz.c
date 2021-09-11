#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// prototypes
//int collatz(int n, int counter); // old prototype that used a counter
int collatz(int n);

// hard coded numbers
const int NUMBERCHECK = 50;

int main()
{

    const int result = collatz(NUMBERCHECK);
    printf("%i\n", result);

}

// The solution from class which avoids using the counter I was using
// I guess maybe I still don't quite have my mind wrapped around what it's returning
// I had the base case and other stuff right but not this more elegant way of returning the value
// we were interested in.
int collatz(int n)
{

    // Set up the base case.
    if(n == 1)
    {
        return 0;
    }
    // if the number is even, we can just divide it by two and call the function again with n
    else if (n % 2 == 0)
    {
        return 1 + collatz(n/2);
    }
    // if the number isn't 1 and isn't even, we can call the function again with this formula
    else
    {
        return 1 + collatz((3 * n) + 1);
    }
}






// My original solution which passed in a counter and kept sending that back in
// int collatz(int n, int counter)
// {


//     // Set up the base case.
//     if(n == 1)
//     {
//         return counter;
//     }
//     // if the number is even, we can just divide it by two and call the function again with n
//     else if (n % 2 == 0)
//     {
//         counter++;
//         return collatz(n/2, counter);
//     }
//     // if the number isn't 1 and isn't even, we can call the function again with this formula
//     else
//     {
//         counter++;
//         return collatz((3 * n) + 1, counter);
//     }
// }








