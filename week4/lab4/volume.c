// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// def some bytes
typedef uint8_t SINGLEBYTE;
typedef int16_t DOUBLEBYTE;

// string = char *
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // Create an array of 44 bytes using the HEADER_SIZE they gave us
    SINGLEBYTE headerBuffer[HEADER_SIZE]; //44

    // Read into the headersize and write that back out to the file. No need to use while in this case its fixed bytes
    // This will get the entire 44 bytes and spit it back out
    // limit it to only the 44 bytes here
    fread(&headerBuffer, sizeof(SINGLEBYTE), HEADER_SIZE, input);
    // this way it will keep where it is in the stream for the while below
    fwrite(&headerBuffer, sizeof(SINGLEBYTE), HEADER_SIZE, output);



    // TODO: Read samples from input file and write updated data to output file
    // NOTE - it looks like it keeps track of where it is in the file stream.
    // I thought I might need to use fseek but this was much easier than I was making it out to be.
    DOUBLEBYTE sample; // easily read my two bytes at a time
    while (fread(&sample, sizeof(DOUBLEBYTE), 1, input))
    {
        // multiply the sample before writing it
        sample = sample * factor;
        fwrite(&sample, sizeof(DOUBLEBYTE), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
