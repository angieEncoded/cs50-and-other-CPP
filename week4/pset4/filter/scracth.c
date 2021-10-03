
            // Deal with upper left edge case
            if (i == 0 && j == 0)
            {
                                // right pixel         // bottom pixel     // caddy corner pixel
                redAverage = round((image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 3);
                greenAverage = round((image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 3);
                blueAverage = round((image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 3);

                // Set the pixels
                image[i][j].rgbtRed = redAverage;
                image[i][j].rgbtGreen = greenAverage;
                image[i][j].rgbtBlue = blueAverage;

                // Go to the next iteration of the loop
                continue;
            }

            // Deal with upper right edge case
            if(i == 0 && j == width -1)
            {
                                    // left pixel                   // bottom pixel                 // caddy corner left
                redAverage = round((image[i][width - 2].rgbtRed + image[i + 1][width - 1].rgbtRed + image[i + 1][width - 2].rgbtRed) / 3);
                greenAverage = round((image[i][width - 2].rgbtGreen + image[i + 1][width - 1].rgbtGreen + image[i + 1][width - 2].rgbtGreen) / 3);
                blueAverage = round((image[i][width - 2].rgbtBlue + image[i + 1][width - 1].rgbtBlue + image[i + 1][width - 2].rgbtBlue) / 3);

                // Set the pixels
                image[i][j].rgbtRed = redAverage;
                image[i][j].rgbtGreen = greenAverage;
                image[i][j].rgbtBlue = blueAverage;

                // Go to the next iteration of the loop
                continue;


            }

            // Deal with rest of top row cases
            if (i == 0) {
                //           Left pixel                right pixel               bottom pixel              bottom right                  bottom left
                redAverage = round((image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 5)
                greenAverage = round((image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 5)
                blueAverage = round((image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 5)

                // Set the pixels
                image[i][j].rgbtRed = redAverage;
                image[i][j].rgbtGreen = greenAverage;
                image[i][j].rgbtBlue = blueAverage;

                // Go to the next iteration of the loop
                continue;
            }

            // Deal with bottom right edge case
            if (i == height - 1 && j == 0)
            {

            }

            // Deal with bottom left edge case
            if (i == height - 1 && j == width - 1)
            {

            }

            // Deal with rest of bottom row cases
            if (i == height - 1)
            {

            }


            // Deal with right edge cases
            if ()

            // Deal with left edge cases


            // Deal with any cases that are NOT edge

