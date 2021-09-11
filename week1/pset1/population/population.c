#include <cs50.h>
#include <stdio.h>


// My prototypes here
int computeYears(int startingSize, int targetPop, int count);


int main(void)
{

    // Prompt the user for the starting population size
    // Check whether that size is smaller than 9 and keep prompting until the user enters a number greater than or equal to 9
    int startingSize;
    do
    {
        startingSize = get_int("Please enter the starting population: ");
    }
    while (startingSize < 9);


    // Prompt the user for a target ending population size
    // Check that the number is greater than or equal to the starting population size and re-prompt as necessary
    int endingSize;
    do
    {
        endingSize = get_int("Please enter your target population and I will compute how many years are required: ");
    }
    while (endingSize < startingSize);


    int expectedYears = 0;

    // Calculate the integer number of years that it will take to reach that population size
    // print the number of years required in this format: Years: numberOfYears
    printf("Years: %i", computeYears(startingSize, endingSize, expectedYears));





}



// This is a recursive function that will keep track of the years in the count variable and return the years. I have been working on learning recursion in javascript
int computeYears(int startingSize, int targetPop, int count)
{
    if (startingSize >= targetPop)
    {
        return count;
    }
    else
    {
        int births, deaths, newTotal;
        births = startingSize / 3;
        deaths = startingSize / 4;
        newTotal = startingSize + (births - deaths);
        count++;
        return computeYears(newTotal, targetPop, count);
    }
}