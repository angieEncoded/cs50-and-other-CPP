#include <stdio.h>
#include <cs50.h>

void printPyramid(int heightOfPyramid);


int main()
{
    // get the input from the user -  we need a number between 1 and 8 inclusive
    int heightOfPyramid = 8;
    // do
    // {
    //     heightOfPyramid = get_int("Please enter a number between 1 and 8: ");
    // }
    // //I remember running into problems using AND before. It doesn't seem to work the way I'd expect it to. OR does get the result I need though.
    // while (heightOfPyramid < 1 || heightOfPyramid > 8);

     printPyramid(heightOfPyramid);

}



void printPyramid(int heightOfPyramid)
{
    int numberOfHashes = 0;


    for (int i =0; i < heightOfPyramid; i++)
    {
        numberOfHashes = heightOfPyramid - (heightOfPyramid - i);

        for (int j = 0; j < numberOfHashes; j++)
        {
           printf("#");
        }
        printf("\n");
    }

}



/*
    // number of spaces we need in front of the line
    int startingSpaces = heightOfPyramid - 1;
    int numberOfHashes = 2; // starting number of hashes will always be 2

    for (int i = 0; i < heightOfPyramid; i++)
    {

        // we always need 1 less than the height of the pyramid
        for (int j = 0; j < startingSpaces; j++)
        {
            printf(" ");
        }

        // The hashes on one side are hashes \ 2
        for (int k = numberOfHashes / 2; k > 0; k--)
        {
            printf("#");
        }

        // print the rest of the hashes (hashes\2)
        for (int k = numberOfHashes / 2; k > 0; k--)
        {
            printf("#");
        }
        printf("\n");
        numberOfHashes += 2;
        startingSpaces--;

    }




*/