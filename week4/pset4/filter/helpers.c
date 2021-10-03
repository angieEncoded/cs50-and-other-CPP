#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /*
        BYTE  rgbtBlue;
        BYTE  rgbtGreen;
        BYTE  rgbtRed;
    */

    double average = 0;
    // HEIGHT LOOP
    for (int i = 0; i < height; i++)
    {
        // WIDTH LOOP
        for (int j = 0; j < width; j++)
        {
            // look at the pixel and average them together - round them to nearest int - these are all ints needed to cast one to a double so it did float point arithmetic
            average = ((double)image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            // Set the pixel's rgb all to that same value
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    /*
        BYTE  rgbtBlue;
        BYTE  rgbtGreen;
        BYTE  rgbtRed;
        sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
        red, green, and blue values should be capped at 255.
        whole numbers between 0 and 255, inclusive.
    */

    // if the rounded value is > 255 set it to 255


    // HEIGHT LOOP
    for (int i = 0; i < height; i++)
    {
        // WIDTH LOOP
        for (int j = 0; j < width; j++)
        {
            // look at the pixel and get the value rounded to the nearest int
            double sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            double sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            double sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Check to make sure no one is bigger than 255
            sepiaRed = (sepiaRed > 255) ? 255 : sepiaRed;
            sepiaGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            sepiaBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;

            // Set the rgb values appropriately
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtBlue = round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE swap = {};

    // HEIGHT LOOP
    for (int i = 0; i < height; i++)
    {

        // WIDTH LOOP
        for (int j = 0, counter = 1; j < width; j++, counter++)
        {

            // Check whether the address of pixels is adjacent or if we've crossed each other and kill the loop
            if (&image[i][j] == &image[i][width - counter] || &image[i][j] > &image[i][width - counter])
            {
                break;
            }


            // Swap the far pixel into the swap
            swap = image[i][width - counter];

            // Swap the current pixel into the far pixel
            image[i][width - counter] = image[i][j];

            // Swap the swap pixel into the near pixel
            image[i][j] = swap;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{


    // My problem was trying to sort everything in place and failing because values changed for pixels
    RGBTRIPLE swapFile[height][width];


    // HEIGHT LOOP
    for (int i = 0; i < height; i++)
    {
        // WIDTH LOOP
        for (int j = 0; j < width; j++)
        {

            double counter = 0;
            double redAverage = 0;
            double greenAverage = 0;
            double blueAverage = 0;

            // Add the current pixel's values first and increment the counter
            redAverage += image[i][j].rgbtRed;
            greenAverage += image[i][j].rgbtGreen;
            blueAverage += image[i][j].rgbtBlue;
            counter++;


            // If there is a left value, add it
            if (j > 0)
            {
                redAverage += image[i][j - 1].rgbtRed;
                greenAverage += image[i][j - 1].rgbtGreen;
                blueAverage += image[i][j - 1].rgbtBlue;
                counter++;
            }

            // If there is a right value, add it
            if (j < width - 1)
            {
                redAverage += image[i][j + 1].rgbtRed;
                greenAverage += image[i][j + 1].rgbtGreen;
                blueAverage += image[i][j + 1].rgbtBlue;
                counter++;
            }

            // If there is a top value, add it
            if (i > 0)
            {
                redAverage += image[i - 1][j].rgbtRed;
                greenAverage += image[i - 1][j].rgbtGreen;
                blueAverage += image[i - 1][j].rgbtBlue;
                counter++;
            }

            // If there is a bottom value, add it
            if (i < height - 1)
            {
                redAverage += image[i + 1][j].rgbtRed;
                greenAverage += image[i + 1][j].rgbtGreen;
                blueAverage += image[i + 1][j].rgbtBlue;
                counter++;
            }

            // If there is a diagonal upper right, add it
            if (i > 0 && j < width - 1)
            {
                redAverage += image[i - 1][j + 1].rgbtRed;
                greenAverage += image[i - 1][j + 1].rgbtGreen;
                blueAverage += image[i - 1][j + 1].rgbtBlue;
                counter++;
            }

            // If there is a diagonal upper left, add it
            if (i > 0 && j > 0)
            {
                redAverage += image[i - 1][j - 1].rgbtRed;
                greenAverage += image[i - 1][j - 1].rgbtGreen;
                blueAverage += image[i - 1][j - 1].rgbtBlue;
                counter++;
            }

            // If there is a diagonal lower right, add it
            if (i < height - 1 && j < width - 1)
            {
                redAverage += image[i + 1][j + 1].rgbtRed;
                greenAverage += image[i + 1][j + 1].rgbtGreen;
                blueAverage += image[i + 1][j + 1].rgbtBlue;
                counter++;
            }


            // If there is a diagonal lower left, add it
            if (i < height - 1 && j > 0)
            {
                redAverage += image[i + 1][j - 1].rgbtRed;
                greenAverage += image[i + 1][j - 1].rgbtGreen;
                blueAverage += image[i + 1][j - 1].rgbtBlue;
                counter++;
            }

            // Divide the averages by the counter and round
            redAverage = round(redAverage / counter);
            greenAverage = round(greenAverage / counter);
            blueAverage = round(blueAverage / counter);




            // Set the new values as needed
            swapFile[i][j].rgbtRed = redAverage;
            swapFile[i][j].rgbtGreen = greenAverage;
            swapFile[i][j].rgbtBlue = blueAverage;

        }
    }



    // Copy the values of swapFile back into the original file
    // HEIGHT LOOP
    for (int i = 0; i < height; i++)
    {
        // WIDTH LOOP
        for (int j = 0; j < width; j++)
        {
            image[i][j] = swapFile[i][j];
        }
    }






    return;
}
