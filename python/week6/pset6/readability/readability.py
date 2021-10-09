# stringOfText = "this is a test for how many letters? this is a test for how many letters. this is a test for how many letters!"
# 28 letters
# stringOfText = "Test"
# ord() will convert to the ascii value - this stands for Ordinal value apparently
# https://en.wikipedia.org/wiki/Ordinal_data_type


def main():

    stringOfText = input("Enter a string: ")

    # Count the number of letters, words, and sentences in the text. Get the reading grade level
    numberOfLetters = getNumberOfLetters(stringOfText)
    # Don't even need the function in python. We just split on the space like in javascript
    numberOfWords = len(stringOfText.split())
    # Still needed my function - no easy way for this
    numberOfSentences = getNumberOfSentences(stringOfText)

    readingGradeLevel = getReadingGradeLevel(
        numberOfLetters, numberOfWords, numberOfSentences)

    if (readingGradeLevel > 16):
        # If it's above grade 16 then print out "Grade 16+""
        print("Grade 16+")
    elif (readingGradeLevel < 1):
        # If the index is before grade 1, then print out "Before Grade 1"
        print("Before Grade 1")
    else:
        # Print the output as "Grade X" where X is the grade number
        print(f"Grade {readingGradeLevel}")


def getReadingGradeLevel(numberOfLetters, numberOfWords, numberOfSentences):

    #  index = 0.0588 * L - 0.296 * S - 15.8
    #  L is the average number of letters per 100 words in the text
    #  S is the average number of sentences per 100 words in the text

    #  Calculate L - average number of letters per 100 words - make sure to cast as needed. Math was ALL KINDS of wrong when these were ints
    L = float(numberOfLetters) / numberOfWords * 100

    #  Calculate S - average number of sentences per 100 words
    S = float(numberOfSentences) / numberOfWords * 100

    #  perform the actual calculation
    index = 0.0588 * L - 0.296 * S - 15.8

    #  round the number before returning it
    # const int rounded = round(index);
    return round(index)


# Count the number of sentences
def getNumberOfSentences(input):

    sentences = 0

    # Step through the string and add 1 for every sentence
    for letter in input:
        if (ord(letter) == 46 or ord(letter) == 33 or ord(letter) == 63):
            sentences += 1

    return sentences


# Convert to lowercase and check that letters are acters between 97-122
def getNumberOfLetters(input):

    letters = 0
    # Step through the string and add 1 to letters for anything that falls between 97 and 122
    for char in input:
        if (ord(char.lower()) >= 97 and ord(char.lower()) <= 122):
            letters += 1

    return letters


if __name__ == "__main__":
    main()
