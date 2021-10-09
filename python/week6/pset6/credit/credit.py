# Used these for testing
# dummyVisa = 4012888888881881
# dummyMasterCard = 5421000000000009
# dummyAmexCard = 4003600000000014
# dummyAmexCard = 378282246310005


def main():

    #  testing
    # cardNumber = dummyAmexCard
    # cardNumber = dummyMasterCard
    # cardNumber = dummyVisa

    # Grab the number of digits
    # numberOfDigits = countNumberOfdigits(cardNumber)
    # print(numberOfDigits)

    # check it for proper length
    # valid = correctNumberOfDigits(numberOfDigits)
    # print(valid)

    # If it has the proper length, then we need to check what kind of card it is
    # print(typeOfCard(cardNumber))

    #  Check if the card number is valid
    # checkCardAlgorithm(cardNumber)

    #  get the number from the user

    while True:
        cardNumber = input("Number: ")

        if(cardNumber.isdigit()):

            result = checkNumber(int(cardNumber))
            print(result)
            break


def countNumberOfDigits(cardNumber):
    count = 0
    cardCount = cardNumber

    #  Divide by 10 until we hit 0
    while (cardCount > 0):
        cardCount = cardCount // 10
        count += 1
    return count

# A function that will make all the checks and return either INVALID or the card type to the user


def checkNumber(cardNumber):

    # Make sure the number is correct first
    numberOfDigits = countNumberOfDigits(cardNumber)
    if (correctNumberOfDigits(numberOfDigits) == False):
        return "INVALID"

    # If we passed that, then check that is passes the algorithm
    if (checkCardAlgorithm(cardNumber) == False):
        return "INVALID"

    # and finally if we passed that check, then return what kind of card it is
    return typeOfCard(cardNumber)


#  Check Luhn's algorithm to make sure we have a valid card number
def checkCardAlgorithm(cardNumber):

    digitsForSecondToLast = 0
    remainingNumbersTotal = 0
    multipliedValueHolder = 0
    cardNumberCounter = cardNumber
    digit = 2  # Our starting digit, which will always be a straight up add to the total 0 mod 0 is undefined

    while (cardNumberCounter > 0):
        #  Starts on the rightmost digit
        if (digit % 2 == 0):
            #  printf("%i", digit)
            remainingNumbersTotal = remainingNumbersTotal + \
                cardNumberCounter % 10  # add the remainder number to the total
            cardNumberCounter = cardNumberCounter // 10  # move to the next
            digit += 1  # increment the digit

        else:  # Starts on the second rightmost digit
            #  Get the multiplied value
            multipliedValueHolder = (cardNumberCounter % 10) * 2

            #  Then run through each of those digits and add to the other running total
            while (multipliedValueHolder > 0):

                digitsForSecondToLast = digitsForSecondToLast + \
                    (multipliedValueHolder % 10)
                multipliedValueHolder = multipliedValueHolder // 10

            #  cleanup
            cardNumberCounter = cardNumberCounter // 10  # move to the next
            digit += 1

    #  Finally add the sums together and check whether the total modulo 10 is 0 if it is, return 1 else return 0
    total = digitsForSecondToLast + remainingNumbersTotal
    # printf("%i\n", total)
    if (total % 10 == 0):
        return True
    else:
        return False


def typeOfCard(cardNumber):

    # Divide by 10 until you have hit the place you want, in this case I need the hundreds place
    # This must be the way that javascript does this behind the scenes. I regret it being the first language I learned.
    firstTwoDigits = cardNumber
    while (firstTwoDigits > 100):
        firstTwoDigits = firstTwoDigits // 10

    # Now get the first digit in case it's a visa
    isVisa = firstTwoDigits
    while (isVisa > 10):
        isVisa = isVisa // 10

    # Check the digits against the numbers we expect
    if (isVisa == 4):
        return "VISA"

    # If it wasn't a visa we have to do the rest of the checks
    # amex starts with 36 or 37
    # mastercard starts with 51,52,53,54,55

    # Check for amex
    if (firstTwoDigits == 34 or firstTwoDigits == 37):
        return "AMEX"

    if (firstTwoDigits == 51 or firstTwoDigits == 52 or firstTwoDigits == 53 or firstTwoDigits == 54 or firstTwoDigits == 55):
        return "MASTERCARD"

    return "INVALID"

# Check if the card has the correct amount of digits to be considered further


def correctNumberOfDigits(numberOfDigits):

    # return 0 if invalid, 1 if valid
    if (numberOfDigits == 13 or numberOfDigits == 15 or numberOfDigits == 16):
        return True
    else:
        return False

#  Count the number of digits in the card


if __name__ == "__main__":
    main()
