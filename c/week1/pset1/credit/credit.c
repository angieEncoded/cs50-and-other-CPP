#include <stdio.h>
#include <cs50.h>

// Prototypes
int countNumberOfDigits(long cardNumber);
int correctNumberOfDigits(int numberOfDigits);
string typeOfCard(long cardNumber);
string checkNumber(long cardNumber);
int checkCardAlgorithm(long cardNumber);

// used these for testing
const long dummyVisa = 4012888888881881;
const long dummyMasterCard = 5421000000000009;
const long dummyAmexCard = 4003600000000014;
//const long dummyAmexCard = 378282246310005;


int main()
{
    // testing
    //long cardNumber;
    //cardNumber = dummyAmexCard;

    // Grab the number of digits
    //const int numberOfDigits = countNumberOfdigits(cardNumber);
    //printf("%i\n", numberOfDigits);


    // check it for proper length
    //const int valid = correctNumberOfDigits(numberOfDigits);
    //printf("%i\n", valid);

    // If it has the proper length, then we need to check what kind of card it is
    //printf("%s\n", typeOfCard(cardNumber));

    // Check if the card number is valid

    //checkCardAlgorithm(cardNumber);



    // get the number from the user
    const long cardNumber = get_long("Number: ");

    const string result = checkNumber(cardNumber);
    printf("%s", result);
}



// A function that will make all the checks and return either INVALID or the card type to the user
string checkNumber(long cardNumber)
{

    // Make sure the number is correct first
    const int numberOfDigits = countNumberOfDigits(cardNumber);
    if (!correctNumberOfDigits(numberOfDigits))
    {
        return "INVALID\n";
    }


    // If we passed that, then check that is passes the algorithm
    if (!checkCardAlgorithm(cardNumber))
    {
        return "INVALID\n";
    }


    // and finally if we passed that check, then return what kind of card it is
    return typeOfCard(cardNumber);

}


// Check Luhn's algorithm to make sure we have a valid card number
int checkCardAlgorithm(long cardNumber)
{

    int digitsForSecondToLast = 0;
    int remainingNumbersTotal = 0;
    int multipliedValueHolder = 0;
    long cardNumberCounter = cardNumber;
    int digit = 2;// Our starting digit, which will always be a straight up add to the total 0 mod 0 is undefined


    while (cardNumberCounter > 0)
    {
        // Starts on the rightmost digit
        if (digit % 2 == 0)
        {
            // printf("%i", digit);
            remainingNumbersTotal = remainingNumbersTotal + cardNumberCounter % 10; // add the remainder number to the total
            cardNumberCounter = cardNumberCounter / 10; // move to the next
            digit++; // increment the digit

        }

        else // Starts on the second rightmost digit

        {
            // Get the multiplied value
            multipliedValueHolder = (cardNumberCounter % 10) * 2;

            // Then run through each of those digits and add to the other running total
            while (multipliedValueHolder > 0)
            {
                digitsForSecondToLast = digitsForSecondToLast + (multipliedValueHolder % 10);
                multipliedValueHolder = multipliedValueHolder / 10;
            }

            // cleanup
            cardNumberCounter = cardNumberCounter / 10; // move to the next
            digit++;
        }

    }


    // Finally add the sums together and check whether the total modulo 10 is 0; if it is, return 1 else return 0
    int total = digitsForSecondToLast + remainingNumbersTotal;
    //printf("%i\n", total);
    if (total % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}













// Figure out what type of card we have
string typeOfCard(long cardNumber)
{

    // Divide by 10 until you have hit the place you want, in this case I need the hundreds place
    // This must be the way that javascript does this behind the scenes. I regret it being the first language I learned.
    long firstTwoDigits = cardNumber;
    while (firstTwoDigits > 100)
    {
        firstTwoDigits = firstTwoDigits / 10;
    }

    // Now get the first digit in case it's a visa
    int isVisa = firstTwoDigits;
    while (isVisa > 10)
    {
        isVisa = isVisa / 10;
    }

    // Check the digits against the numbers we expect
    if (isVisa == 4)
    {
        return "VISA\n";
    }

    // If it wasn't a visa we have to do the rest of the checks
    // amex starts with 36 or 37
    // mastercard starts with 51,52,53,54,55

    // Check for amex
    if (firstTwoDigits == 34 || firstTwoDigits == 37)
    {
        return "AMEX\n";
    }

    if (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55)
    {
        return "MASTERCARD\n";
    }

    return "INVALID\n";

}




// Check if the card has the correct amount of digits to be considered further
int correctNumberOfDigits(int numberOfDigits)
{

    // return 0 if invalid, 1 if valid
    if (numberOfDigits == 13 || numberOfDigits == 15 || numberOfDigits == 16)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}


// Count the number of digits in the card
int countNumberOfDigits(long cardNumber)
{
    int count = 0;
    long cardCount = cardNumber;

    // Divide by 10 until we hit 0
    while (cardCount > 0)
    {
        cardCount = cardCount / 10;
        count++;
    }
    return count;
}