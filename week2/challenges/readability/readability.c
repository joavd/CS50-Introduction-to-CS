#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int calculate_grade(string s);

int main(void)
{
    // Final grade of the given text
    int grade;
    // Reads the text from the input
    string text = get_string("Text: ");

    //Calls the calculate function and returns it's value
    grade = calculate_grade(text);

    // Depending on the grade we print a different result
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Calculates the grade of a given text, by the grading system provided by CS50
int calculate_grade(string s)
{
    // The value of the required values, we start Words at 1 to correctly adress it
    int numLetters = 0;
    int numWords = 1;
    int numSentences = 0;
    int index;

    // Goes along the string and check fr each char
    for (int i = 0; i < strlen(s); i++)
    {
        // If it's an alphabetical char we count a letter
        if (isalpha(s[i]))
        {
            numLetters++;
        }
        // If it's a space we count a word
        if (isspace(s[i]))
        {
            numWords++;
        }
        // If it's one of the given signals we count a sentence (even for something like Mr. X)
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            numSentences++;
        }
    }

    // We convert the values to float in order to correctly calculate them, otherwise int cuts the decimal part
    float L = (float) numLetters / numWords * 100;
    float S = (float) numSentences / numWords * 100;

    // For the final value we need to round it using
    index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}