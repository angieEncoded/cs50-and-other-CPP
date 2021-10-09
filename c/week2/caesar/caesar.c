#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// test constants
//const string TEST = "hello";

// Prototypes
void printEncryptedText(string inputString, int key);


int main(int argc, string argv[])
{
    // If there are more than two arguments exit - tested and working
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    // Check to see if it's a decimal digit - loop through all the characters and let it through if they are all digits
    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        // use the isdigit method to check whether we are sending in all numbers
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //If all those checks passed, convert the argument to an integer for us to pass into the function
    int key = atoi(argv[1]);

    const string userInput = get_string("plaintext: ");
    printEncryptedText(userInput, key);

    //printf("%s\n", result);

    return 0;
}




void printEncryptedText(string inputString, int key)
{

    // If the user sends in a ridiculously long key, we'll need to wrap. Get the remainder after dividing by 26 letters
    if (key > 26)
    {
        key = key % 26;
    }
    printf("%i\n", key);


    printf("ciphertext: ");
    // step through the string and see what the character is - print out for now
    for (int i = 0, length = strlen(inputString); i < length; i++)
    {

        // If it isn't alpha leave it alone
        if (!isalpha(inputString[i]))
        {
            printf("%c", inputString[i]);
        }

        // Check if it is an uppercase letter
        if (isupper(inputString[i]))
        {
            // Now we have to calculate the new letter's location between 65 - 91
            // We already took care of any around-the-world wrapping.
            // calculate the distance from the upper limit
            int difference = 91 - inputString[i]; // needed an extra 1 in this subtraction. off by one error...

            // If it's greater than the key, no extra calcs need to be done.
            if (difference > key)
            {
                printf("%c", inputString[i] + key);
            }
            // If that's not the case, then we need to subtract the difference from the key and print the character at 65 + key
            else
            {
                difference = key - difference;
                printf("%c", 65 + difference);
            }
            //printf("Its uppercase %c\n", inputString[i]);
        }


        //THE PROBLEM IS IN HERE THE UPPERCASE IS WORKING FINE CHECK YOUR MATH IN HERE
        // Check if it is a lowercase letter
        if (islower(inputString[i]))
        {
            // Now we have to calculate the new letter's location between 97 - 122 - I need to put this in a function. This copy paste was a bad idea
            // We already took care of any around-the-world wrapping.
            // calculate the distance from the upper limit
            int difference = 123 - inputString[i]; // needed an extra 1 in this subtraction. off by one error....

            // If it's greater than the key, no extra calcs need to be done.
            if (difference > key)
            {
                printf("%c", inputString[i] + key);
            }
            // If that's not the case, then we need to subtract the difference from the key and print the character at 65 + key
            else
            {
                difference = key - difference;
                printf("%c", 97 + difference);
            }
            //printf("Its uppercase %c\n", inputString[i]);
        }

    }
    printf("\n");


}