#include <cs50.h>
#include <stdio.h>


int main (void){

    // Prompt the user for the data
    const char c = get_char("Do you agree? ");


    // This needs to be == to check for equality and we have to use single quotes for single characters
    if(c == 'y' || c == 'Y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("Not Agreed\n");
    }
}