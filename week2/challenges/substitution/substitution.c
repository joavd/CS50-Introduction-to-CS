#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool validate_key(string s);
void encrypt(string key, string text);

int main(int argc, string argv[])
{
    // Value to be returned at the end of the program 0 = good, 1 = bad
    int returnVal = 1;
    // Key given by the user
    string key = argv[1];
    // Text input from the user
    string plainTxt = "";

    // Checks there are exactly 2 arguments, name of the program & key
    if (argc == 2)
    {
        // Checks if the key is valid, if it is proceeds to encrypt it
        if (validate_key(argv[1]))
        {
            // Gets the input from the user
            plainTxt = get_string("plaintext: ");
            printf("ciphertext: ");
            // Encrypts the key and prints it
            encrypt(key, plainTxt);
            // Returns success
            returnVal = 0;
        }
    }
    // If it's not valid displays how tu run the program
    else
    {
        printf("Usage: ./substitution key\n");
    }

    return returnVal;
}

// Validates the key provided
bool validate_key(string key)
{
    // If the key is valid
    bool isValid = true;
    int keyNum = 26;

    // Checks it the key provided is exactly 26 characters
    if (strlen(key) == keyNum)
    {
        // And then checks each character to see if they're all alphabetic
        for (int i = 0; i < keyNum; i++)
        {
            // If it's not alphabetic it returns an error message
            if (!isalpha(key[i]))
            {
                printf("Key must only contain alphabetic characters\n");
                isValid = false;
                break;
            }

            // If it's not valid it breaks
            if (!isValid)
            {
                break;
            }

            // checks if there are no repeated characters in the ky
            for (int j = 0; j < 26; j++)
            {
                if (!(i == j) && key[i] == key[j])
                {
                    printf("Key must not contain repeated characters\n");
                    isValid = false;
                    break;
                }
            }
        }
    }
    // Displays an error if it's not 26 chars
    else
    {
        printf("Key must contain exactly 26 characters\n");
        isValid = false;
    }

    return isValid;
}

// Encrypts the given input and prints it
void encrypt(string key, string text)
{
    // Letters of the alphabet used to compare the position
    char LETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    // Goes along all the inputted text in order to encrypt
    for (int i = 0; i < strlen(text); i++)
    {
        // If it's a letter from the alphabet it proceeds to encrypt it
        if (isalpha(text[i]))
        {
            // If the current letter is upper case it compares it directly
            if (isupper(text[i]))
            {
                // Seaches the alhabet
                for (int j = 0; j < strlen(LETTERS); j++)
                {
                    // Checks the position of the same letter on the alphabet
                    if (text[i] == LETTERS[j])
                    {
                        printf("%c", toupper(key[j]));
                    }
                }
            }
            // If the current letter is lower case it first converts it before comparing
            if (islower(text[i]))
            {
                // Seaches the alhabet
                for (int j = 0; j < strlen(LETTERS); j++)
                {
                    // Checks the position of the same letter on the alphabet
                    if (toupper(text[i]) == LETTERS[j])
                    {
                        printf("%c", tolower(key[j]));
                    }
                }
            }
        }
        // If not it simply leaves it as it is
        else
        {
            printf("%c", text[i]);
        }
    }

    printf("\n");
}