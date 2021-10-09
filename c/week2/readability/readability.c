#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// prototypes
int getNumberOfLetters(string input);
int getNumberOfWords(string input);
int getNumberOfSentences(string input);
int getReadingGradeLevel(int numberOfLetters, int numberOfWords, int numberOfSentences);

//const string TESTSTRING = "this is a test for how many letters? this is a test for how many letters. this is a test for how many letters!"; // 28 letters

int main()
{

    // Get a string of text
    const string stringOfText = get_string("Text: ");


    // Count the number of letters, words, and sentences in the text. Get the reading grade level
    const int numberOfLetters = getNumberOfLetters(stringOfText);
    const int numberOfWords = getNumberOfWords(stringOfText);
    const int numberOfSentences = getNumberOfSentences(stringOfText);
    const int readingGradeLevel = getReadingGradeLevel(numberOfLetters, numberOfWords, numberOfSentences);

    //printf("%i\n", readingGradeLevel);
    if (readingGradeLevel > 16)
    {
        // If it's above grade 16 then print out "Grade 16+""
        printf("Grade 16+\n");
    }
    else if (readingGradeLevel < 1)
    {
        // If the index is before grade 1, then print out "Before Grade 1"
        printf("Before Grade 1\n");
    }
    else
    {
        // Print the output as "Grade X" where X is the grade number
        printf("Grade %i\n", readingGradeLevel);
    }

    // tests
    // printf("%i\n", numberOfLetters(TESTSTRING));
    // printf("%i\n", numberOfWords(TESTSTRING));
    // printf("%i\n", numberOfSentences(TESTSTRING));
}

// My functions below here
int getReadingGradeLevel(int numberOfLetters, int numberOfWords, int numberOfSentences)
{
    // index = 0.0588 * L - 0.296 * S - 15.8
    // L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text

    // Calculate L - average number of letters per 100 words - make sure to cast as needed. Math was ALL KINDS of wrong when these were ints
    const double L = (double) numberOfLetters / numberOfWords * 100;

    // Calculate S - average number of sentences per 100 words
    const double S = (double) numberOfSentences / numberOfWords * 100;

    // perform the actual calculation
    double index = 0.0588 * L - 0.296 * S - 15.8;

    // round the number before returning it
    //const int rounded = round(index);
    return round(index);


}

// Count the number of sentences
int getNumberOfSentences(string input)
{
    int sentences = 0;

    // Step through the string and add 1 for every sentence
    for (int i = 0; i < strlen(input); i++)
    {
        if ((int)input[i] == 46 || (int)input[i] == 33 || (int)input[i] == 63)
        {
            sentences++;
        }
    }

    return sentences;
}

// Count the number of words
int getNumberOfWords(string input)
{
    int words = 0;
    // Check if there is at least one word since this will not account for the final word.
    if (strlen(input) > 0)
    {
        words = 1;
    }

    // Step through the string and add 1 for every word,
    for (int i = 0; i < strlen(input); i++)
    {
        if ((int)input[i] == 32)
        {
            words++;
        }
    }

    return words;
}

// Convert to lowercase and check that letters are characters between 97-122
int getNumberOfLetters(string input)
{
    int letters = 0;
    char currentLetter;
    // Step through the string and add 1 to letters for anything that falls between 97 and 122
    for (int i = 0; i < strlen(input); i++)
    {

        if ((int)tolower(input[i]) >= 97 && (int)tolower(input[i]) <= 122)
        {
            letters++;
        }
    }

    return letters;
}

