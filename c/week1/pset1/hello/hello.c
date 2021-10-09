#include <stdio.h>
#include <cs50.h>


int main(void)
{


    // Prompt the user for a name
    const string userName = get_string("Please enter your name: ");



    // Print out a greeting to the user
    printf("hello, %s\n", userName);


}