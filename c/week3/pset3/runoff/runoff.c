#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // look for the candidate in the array. if it's found, then update preferences for the voter
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    // voter.forEach((vote, index) => {
    //if vote[index] = valid candidate
    // do something and then break out of inner loop
    // else move to next index and check again and then check again

    //})

    // outer loop of the voters
    for (int voter = 0; voter < voter_count; voter++)
    {
        // inner loop to check the ranks
        for (int ranksAcross = 0; ranksAcross < 3; ranksAcross++)
        {
            // if candidate at the [voter][ranksAcross] location is still in the race, add a vote and break the loop
            if (candidates[preferences[voter][ranksAcross]].eliminated == false)
            {
                candidates[preferences[voter][ranksAcross]].votes += 1;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    // if someone has won with over 50% of the vote, then print the winner and return true
    // determine what constitutes 50%+ - voter_count / 2 + 1
    // if candidates's votes > votercount / 2 + 1 then print the winner and return true
    const int majority = voter_count / 2 + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // write out the total number of votes
    int numberOfVotes = voter_count;

    // now figure out who has the lowest amount of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes < numberOfVotes)
        {
            numberOfVotes = candidates[i].votes;
        }
    }

    return numberOfVotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // if the non-eliminated candidates have the same number of votes, it's a tie
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate is still in the running
        if (candidates[i].eliminated == false)
        {
            // Check whether the number of votes matches min.
            if (candidates[i].votes == min)
            {
                continue;
            }
            else
            {
                return false;
            }

        }
    }

    return true;

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    // remove anyone still in the race that has the min number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
