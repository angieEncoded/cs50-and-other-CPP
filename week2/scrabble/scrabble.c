#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
//              a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q,  r, s, t, u, v, w, x, y, z
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};


// protoype given to us
int compute_score(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //compute_score("TEST");

    //TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }


}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    // loop through each letter of the word.
    // The array is 0-26
    // Need to determine the number value of the letter in question first, then pick that value out of the array

    char checkChar;
    int charNum;
    int score = 0;

    // Loop through each character of the word
    for (int i = 0; i < strlen(word); i++)
    {

        // convert it to lowercase to cut the checks in half
        checkChar = tolower(word[i]);

        // Now convert it to the int on the ASCII it belongs to
        charNum = (int)checkChar;

        // Subtract 97 from that number to get where it should fall in the 0-26 chars
        charNum = charNum - 97;

        // if the character doesn't actually fall within our table, score will be 0
        if (charNum < 0 || charNum > 25)
        {
            score = score + 0;
        }
        else
        {
            // Check that location in the array for the score
            score = score + POINTS[charNum];
        }

        //printf("%i\n", charNum);

    }
    //printf("%i\n", score);
    return score;

}

// Thoughts below here
// Determine where it falls in the array of scores...
// This is another math-relationship issue isnt it...
// lets see. how about we change it to lowercase first and cut in half the checks we need to do
// Then... this is a calculation from the ascii table huh
// must be, subtract 97 if we are doing lowercase will give us the location in the array