#include <cs50.h>
#include <stdio.h>

int main(void)
{

    string answer = get_string("What's your name? ");


    // Placeholder similar to string interpolation in js
    printf("Hello, %s\n", answer);

}