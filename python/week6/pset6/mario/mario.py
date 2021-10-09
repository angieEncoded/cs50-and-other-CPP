# there is apparently a different operator for INTEGER division
# 'float' object cannot be interpreted as an integer
# https://stackoverflow.com/questions/19824721/i-keep-getting-this-error-for-my-simple-python-program-typeerror-float-obje

def main():

    # Get the input from the user - reject anything that isn't a positive integer
    while True:

        heightOfPyramid = input("Please enter a height: ")
        if (heightOfPyramid.isdigit()):
            if (int(heightOfPyramid) >= 1 and int(heightOfPyramid) < 9):
                break

    # convert the string to an int
    heightOfPyramid = int(heightOfPyramid)

    # Call the function that will print the pyramid
    printPyramid(heightOfPyramid)

# define a function to deal with printing the height of the pyramid


def printPyramid(heightOfPyramid):
    startingSpaces = heightOfPyramid - 1
    numberOfHashes = 2

    for i in range(heightOfPyramid):
        for j in range(startingSpaces):
            print(" ", end="")

        # Syntax for counting backward in this for loop is the starting count, where to count to, and how much to decrement by
        for k in range(numberOfHashes // 2, 0,  -1):
            print("#", end="")

        # print the spaces in the middle
        print("  ", end="")

        # print the second row of hashes
        for k in range(numberOfHashes // 2, 0, -1):
            print("#", end="")
        print("")
        numberOfHashes += 2
        startingSpaces -= 1


main()
