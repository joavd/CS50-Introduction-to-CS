#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// Computes the score of each word
int compute_score(string word);
// Checks how many points each character is worth
int check_char(char c);

int main(void)
{
    // Stores the winner of the match
    string winner = "";
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Prints the winner
    if (score1 == score2)
    {
        winner = "Tie!\n";
    }
    else if (score1 > score2)
    {
        winner = "Player 1 wins!\n";
    }
    else 
    {
        winner = "Player 2 wins!\n";
    }

    printf("%s", winner);
}

// Computes the score of the word
int compute_score(string word)
{
    int score = 0;

    // Checks each character in the word to know how many points it's worth
    for (int i = 0; i < strlen(word); i++)
    {
        score += check_char(toupper(word[i]));
    }

    return score;
}

// Checks how much each character is worth
int check_char(char c)
{
    int points = 0;

    // Compares the LETTERS array to the POINTS array to get it's value
    for (int i = 0; i < sizeof(LETTERS); i++)
    {
        if (c == LETTERS[i])
        {
            points = POINTS[i];
            break;
        }
    }

    return points;
}
