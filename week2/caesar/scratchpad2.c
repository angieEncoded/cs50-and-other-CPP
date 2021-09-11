#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// prototypes
char rotateLetter(char inputLetter, char upperOrLower);
string getEncryptedText(string inputString);

const string TESTSTRING = "This is a text, string, do something with it.";


int main(int argc, string argv[])
{

    // accept a single command line argument, no more, no less.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    printf("%s\n", argv[1]);

    // Check to see if it's a decimal digit - loop through all the character
    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        // use the isdigit method to check whether we are sending in all numbers
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }


    // Get the string from the user
   //const string userInput = get_string("plaintext: ");

    // send the string into the function that will return the encrypted string

    const string encryptedText = getEncryptedText(TESTSTRING);
    printf("%s", encryptedText);


return 0;

}





// functions
string getEncryptedText(string inputString)
{
    // Set up a place to store the encrypted text
    string encryptedString = "";

    //char *strcat(char *dest, const char *src);
    // Iterate over the string
    for (int i = 0, length = strlen(inputString); i < length; i++)
    {
        //printf("%c\n", inputString[i]);
        // start out by just putting each letter back in the string
        //encryptedString += inputString[i];
        strcat(encryptedString, inputString[i]);
    }

    return encryptedString;
}


char rotateLetter(char inputLetter, char upperOrLower)
{
    char encryptedLetter = inputLetter;
    return encryptedLetter;
}