#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    int imageCount = 0;
    char *infile = argv[1];
    FILE *inptr;
    BYTE inputBuffer[512];
    char filename[8];
    FILE *img;

    // Checks if there is exactly 1 command argument and gives feedback if not
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Tries to open the given file, and if it can't finishes the program
    inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Reads data from the file, in chunks of 512 bytes
    while (fread(&inputBuffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Checks if the first 4 bytes are of a JPEG file
        if (inputBuffer[0] == 0xff && inputBuffer[1] == 0xd8 && inputBuffer[2] == 0xff && ((inputBuffer[3] & 0xf0) == 0xe0))
        {
            // If it's not the 1st image it closes the current file
            if (imageCount != 0)
            {
                fclose(img);
            }

            // Defines the filename and sets it, and after it increments the image count to update the name
            sprintf(filename, "%03i.jpg", imageCount);
            img = fopen(filename, "w");
            imageCount++;
        }

        // If there's already an open file, writes to it
        if (imageCount != 0)
        {
            fwrite(inputBuffer, 1, BLOCK_SIZE, img);
        }
    }

    fclose(img);
    fclose(inptr);

    return 0;
}