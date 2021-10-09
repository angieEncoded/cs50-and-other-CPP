
// functions
string getEncryptedText(string inputString)
{
    string encryptedString = "";

    // Iterate over each character.
    for (int i = 0, length = strlen(inputString); i < length; i++)
    {
        // If it's not an alpha character, don't bother swapping it.
        if (!isalpha(inputString[i] || isspace(inputString[i])))
        {
            encryptedString += inputString[i];
        }
        // Otherwise it must be a character we need to deal with
        else
        {
            // If it is uppercase send in a u to the next function
            if(isupper(inputString[i]))
            {
                encryptedString += rotateLetter(inputString[i], 'u');
            }
            else
            {
                encryptedString += rotateLetter(inputString[i], 'u');
            }
        }

    }

    return encryptedString;

}


char rotateLetter(char inputLetter, char upperOrLower)
{
    char encryptedLetter = inputLetter;
    return encryptedLetter;
}