// a cleaner file where I can just deal with individual functions. Holy macaroni, there's no way to test the blarb they gave us

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// preferences[i][j] is jth preference for voter i
int preferences[10][3];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[3];

// some dummy data - candidates and the ranked votes preferences
candidates[0].name = "Babs";
candidates[0].votes = 0
candidates[0].eliminated = false;
candidates[1].name = "Rory";
candidates[1].votes = 0
candidates[1].eliminated = false;
candidates[2].name = "Bubble";
candidates[2].votes = 0
candidates[2].eliminated = false;


// Voter 0
preferences[0][0] = 1;
preferences[0][1] = 3;
preferences[0][2] = 2;
// Voter 1
preferences[1][0] = 2;
preferences[1][1] = 3;
preferences[1][2] = 1;
// Voter 2
preferences[2][0] = 2;
preferences[2][1] = 1;
preferences[2][2] = 3;
// Voter 3
preferences[3][0] = 3;
preferences[3][1] = 1;
preferences[3][2] = 2;
// Voter 4
preferences[4][0] = 1;
preferences[4][1] = 2;
preferences[4][2] = 3;
// Voter 5
preferences[5][0] = 3;
preferences[5][1] = 1;
preferences[5][2] = 2;
// Voter 6
preferences[6][0] = 3;
preferences[6][1] = 2;
preferences[6][2] = 1;
// Voter 7
preferences[7][0] = 1;
preferences[7][1] = 2;
preferences[7][2] = 3;
// Voter 8
preferences[8][0] = 3;
preferences[8][1] = 1;
preferences[8][2] = 2;
// Voter 9
preferences[9][0] = 1;
preferences[9][1] = 2;
preferences[9][2] = 3;


// Numbers of voters and candidates
int voter_count = 10;
int candidate_count = 3;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);



int main()
{




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
    for(int voter = 0; voter < voter_count; voter++)
    {
        // inner loop to check the ranks
        for (int ranksAcross = 0; ranksAcross < 3; ranksAcross++)
        {
            // if candidate at the [voter][ranksAcross] location is still in the race, add a vote and break the loop
            if(candidates[preferences[voter][ranksAcross]].eliminated == false)
            candidates[preferences[voter][ranksAcross]].votes += 1;
            break;
        }
    }

    return;
}























// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // look for the candidate in the array. if it's found, then update preferences for the voter
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i; // candidate's number will be i
            return true;
        }
    }

    return false;
}

