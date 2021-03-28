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
        candidates[i].name = argv[i + 1];
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
    // Return variable, true if it's a valid vote, false otherwise
    bool valid = false;

    // Checks each candidate to see if the voted name is present
    for (int i = 0; i < candidate_count; i++)
    {
        // If it's present it adds one to his counting and returns true
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            valid = true;
            break;
        }
    }

    return valid;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Stores the highest votest of the candidates
    int highest_votes = 0;

    // Loops through the array to find the highest votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_votes < candidates[i].votes)
        {
            highest_votes = candidates[i].votes;
        }
    }

    // Loops through the array to print the highest votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}

