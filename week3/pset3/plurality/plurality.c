#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // skip the first argument which is program name
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

    // if the vote matches the name of one of the candidates, add to their total vote +1 then return true
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate temp[1]; // give myself a swap location
    // determine the winner with the simple bubble sort

    // Bubble sort here. Seems fine. Maybe I'll have to work out how to do a merge sort in the next exercise.
    int numberOfSwaps = 1; // need a starting point of non-zero number
    while (numberOfSwaps != 0)
    {
        numberOfSwaps = 0; // set it back to 0 inside
        for (int i = 0; i < candidate_count - 1; i++) // try not to hit the bounds of the array
        {
            if (candidates[i].votes < candidates[i + 1].votes) // if the one on the left is less, we want to send it to the back
            {
                numberOfSwaps++; // increment the counter so we hit the while condition again
                temp[0] = candidates[i + 1]; // swap the higher number into the temp location
                candidates[i + 1] = candidates[i]; // move the lower number to the one previously taken by the higher one
                candidates[i] = temp[0]; // Move the larger number from the temp location into i
            }
        }
    }

    int howManyToPrint = 1; // set up a counter to see how many positions in the array we need to print
    // The sorting is working, but now it needs to print out multiple winners if they are tied
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // check if the first two candidates got the same amount of votes.
        if (candidates[i].votes == candidates[i + 1].votes)
        {
            // add 1 to my counter if we need to print multiple
            howManyToPrint++;
        }
        else
        {
            break; // leave the loop if there's nothing to do.
        }
    }

    // print out the candidates per amount of howManyToPrint
    for (int i = 0; i < howManyToPrint; i++)
    {
        printf("%s\n", candidates[i].name);
    }


    return;
}


