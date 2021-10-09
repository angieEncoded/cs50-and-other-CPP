#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const int CHUNK_SIZE = 512;
// def some bytes
typedef uint8_t SINGLEBYTE;
typedef int16_t DOUBLEBYTE;


int main(int argc, char *argv[])
{

// First let's make sure we have the right number of arguments

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover filename \n");
        return 1;
    }

    // The argument is in the argument vector
    //printf("%s", argv[1]);

    // Open the file for reading
    FILE *forensicImage = fopen(argv[1], "r");

    // Make sure that the file could be opened (page 363 recommendation)
    if (forensicImage == NULL)
    {
        printf("Could not be opened");
        return 1;
    }

    // Set up a counter to write out our filenames
    int counter = 0;

    // set up a while loop to read chunks of 512 bytes at a time
    SINGLEBYTE buffer[CHUNK_SIZE];
    char filename[8];        // Set up the filename - big enough character array for our name
    FILE *recoveredImage = NULL;


    // This takes a place to write the chunk into, the size of the chunk, how many chunks, and the file we are reading from
    while (fread(&buffer, sizeof(CHUNK_SIZE), 1, forensicImage))
    {



        // Check that we might have found a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // We know we are on the first jpeg. Open a file for writing
            if (counter == 0)
            {


                sprintf(filename, "%03i.jpg", counter);
                recoveredImage = fopen(filename, "w");

                // Make sure the file could be opened
                if (recoveredImage == NULL)
                {
                    printf("Could not be opened");
                    return 1;
                }

            }
            else
            {
                // Close the previous file and then open another one to write to
                fclose(recoveredImage);

                sprintf(filename, "%03i.jpg", counter);
                recoveredImage = fopen(filename, "w");

                // Make sure the file could be opened
                if (recoveredImage == NULL)
                {
                    printf("Could not be opened");
                    return 1;
                }
            }

            counter++;
        }


        // Check for the end of the entire file


        // Check if a file is open and write to it
        if (recoveredImage != NULL)
        {
            fwrite(&buffer, sizeof(CHUNK_SIZE), 1, recoveredImage);
        }

    }



    // Close the file when we are done with it (per page 365)
    fclose(recoveredImage);
    fclose(forensicImage);



    return 0;


}