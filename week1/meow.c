#include <stdio.h>
#include <cs50.h>

// Throw the prototypes up here. We promise the compiler that this will exist
void meow(const int numberOfMeows);



int main(void)
{

    // Make a meow three times
    // printf("meow\n");
    // printf("meow\n");
    // printf("meow\n");


    // Copy and paste is a bad instinct
    // for (int i = 0; i < 3; i++)
    // {
    //     meow();
    // }

    // What if we want to run the for loop inside the meow?
    meow(3);



}


// Create a function that returns void and doesn't take any parameters
// By convention we put the functions at the bottom and a prototype up top
void meow(const int numberOfMeows)
{
    // Now we can take in the parameter and run it here
    for (int i = 0; i < numberOfMeows; i++)
    {
        printf("Meow\n");
    }

}