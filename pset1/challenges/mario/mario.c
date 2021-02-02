#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    // Ask for the initial population, until it's bigger or equal than 9
    while (height <= 0 || height >= 9)
    {
        height = get_int("Height:");
    }

    // Prints each row
    for (int row = 0; row < height; row++)
    {
        // Prints the spaces
        for (int spaces = (height - 1) - (row + 1); spaces >= 0; spaces--)
        {
            printf(" ");
        }
        // Prints the hashes
        for (int hashes = row + 1; hashes > 0; hashes--)
        {
            printf("#");
        }
        printf("  ");
        for (int hashes = row + 1; hashes > 0; hashes--)
        {
            printf("#");
        }
        printf("\n");
    }
}
