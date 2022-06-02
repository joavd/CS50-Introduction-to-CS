#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loops through each position in the array
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Calculates the average in a greyscale and applies it for each color
            float average = (float)(image[row][column].rgbtRed + image[row][column].rgbtGreen + image[row][column].rgbtBlue) / 3;
            int roundedAverage = round(average);

            image[row][column].rgbtRed = roundedAverage;
            image[row][column].rgbtGreen = roundedAverage;
            image[row][column].rgbtBlue = roundedAverage;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loops through each row
    for (int row = 0; row < height; row++)
    {
        // Loops through half a row, excluding the middle odd number
        for (int column = 0; column < width / 2; column++)
        {
            // Flips the 1st half with the 2nd one, using temporary variables to store the information
            const int inverseColumn = width - column - 1;
            const int tempRed = image[row][column].rgbtRed;
            const int tempGreen = image[row][column].rgbtGreen;
            const int tempBlue = image[row][column].rgbtBlue;

            image[row][column].rgbtRed = image[row][inverseColumn].rgbtRed;
            image[row][column].rgbtGreen = image[row][inverseColumn].rgbtGreen;
            image[row][column].rgbtBlue = image[row][inverseColumn].rgbtBlue;

            image[row][inverseColumn].rgbtRed = tempRed;
            image[row][inverseColumn].rgbtGreen = tempGreen;
            image[row][inverseColumn].rgbtBlue = tempBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creates a temporary array to have the original data
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loops through each position in the array
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Puts default value equal to the current position in the array
            float blurRed = 0;
            float blurGreen = 0;
            float blurBlue = 0;
            int numberOfNears = 0;

            // For each position in the array, loops around it
            for (int nearRow = row - 1; nearRow <= row + 1; nearRow++)
            {
                // If current row position is out of bounds it skips
                if (nearRow < 0 || nearRow >= height)
                {
                    continue;
                }

                for (int nearColumn = column - 1; nearColumn <= column + 1; nearColumn++)
                {
                    // Checks if the nearby position is within the array
                    if (nearColumn >= 0 && nearColumn < width)
                    {
                        blurRed += temp[nearRow][nearColumn].rgbtRed;
                        blurGreen += temp[nearRow][nearColumn].rgbtGreen;
                        blurBlue += temp[nearRow][nearColumn].rgbtBlue;
                        numberOfNears++;
                    }
                }
            }

            // Applies the blurred value
            image[row][column].rgbtRed = round((float)(blurRed / numberOfNears));
            image[row][column].rgbtGreen = round((float)(blurGreen / numberOfNears));
            image[row][column].rgbtBlue = round((float)(blurBlue / numberOfNears));
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Matrixes to check edges
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Creates a temporary array to have the original data
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loops through each position in the array
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Puts default value equal to the current position in the array
            float gxRed = 0;
            float gyRed = 0;
            float gxGreen = 0;
            float gyGreen = 0;
            float gxBlue = 0;
            float gyBlue = 0;

            // For each position in the array, loops around it
            for (int nearRow = row - 1; nearRow <= row + 1; nearRow++)
            {
                // If current row position is out of bounds it skips
                if (nearRow < 0 || nearRow >= height)
                {
                    continue;
                }

                for (int nearColumn = column - 1; nearColumn <= column + 1; nearColumn++)
                {
                    // Checks if the nearby position is within the array
                    if (nearColumn >= 0 && nearColumn < width)
                    {
                        // Converts the nearRow back to the -1,0,1
                        int convertedRow = nearRow - row + 1;
                        int convertedColumn = nearColumn - column + 1;

                        // Gets the value for gx and gy for all colors of current pixel
                        gxRed += temp[nearRow][nearColumn].rgbtRed * gx[convertedRow][convertedColumn];
                        gyRed += temp[nearRow][nearColumn].rgbtRed * gy[convertedRow][convertedColumn];
                        gxGreen += temp[nearRow][nearColumn].rgbtGreen * gx[convertedRow][convertedColumn];
                        gyGreen += temp[nearRow][nearColumn].rgbtGreen * gy[convertedRow][convertedColumn];
                        gxBlue += temp[nearRow][nearColumn].rgbtBlue * gx[convertedRow][convertedColumn];
                        gyBlue += temp[nearRow][nearColumn].rgbtBlue * gy[convertedRow][convertedColumn];
                    }
                }
            }

            // Applies the method to calculate the edges
            int edgeRed = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int edgeGreen = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int edgeBlue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // If it's bigger, prevents overflow
            if (edgeRed >= 255)
            {
                edgeRed = 255;
            }
            if (edgeGreen >= 255)
            {
                edgeGreen = 255;
            }
            if (edgeBlue >= 255)
            {
                edgeBlue = 255;
            }

            // Applies the edge values
            image[row][column].rgbtRed = edgeRed;
            image[row][column].rgbtGreen = edgeGreen;
            image[row][column].rgbtBlue = edgeBlue;
        }
    }

    return;
}
