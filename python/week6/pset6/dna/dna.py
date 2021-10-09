import csv
import sys
import re
# This was hands down the hardest so far. I don't know if it's because I have been so immersed in
# C++ and Javascript or what, but I had a LOT of trouble here with python. Things like accessing
# values in obects that is now second nature is really, really hard here. Interesting language,
# but maybe just not for me.

# Require the name of a csv file as first command line argument
# require the name of a text file with the dna to identify as the second


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: `python dna.py dnaData.csv stringToSearchFor.txt`")

    # Read all the contents into memory
    dnaRecords = []  # create an empty list for the records

    # I am spending way too much time on this. I'm just opening it twice.

    # open the csv file
    file = open(sys.argv[1], "r")
    dictionaryReader = csv.DictReader(file)
    for row in dictionaryReader:
        dnaRecords.append(row)  # Put the candidate data in memory
    file.close()

    file = open(sys.argv[1], "r")
    headerReader = csv.reader(file)
    dnaStringsToSearch = next(headerReader)  # first row of the data
    del dnaStringsToSearch[0]  # kill the first item which is name
    file.close()

    # print(dnaRecords)
    # print(dnaStringToSearch)

    file = open(sys.argv[2], "r")
    dnaInQuestion = file.read()  # get the dna we are looking at
    file.close()

    results = []
    # print(dnaInQuestion)
    for item in dnaStringsToSearch:
        results.append({item: searchString(item, dnaInQuestion)})

    # print(results)
    # print(dnaRecords)

    # Now compare to each person to see if they are a match

    # Outer loop to go through all the people in the list
    dnaMatch = ""
    for person in dnaRecords:
        flag = True

        # Inner loop to go through all the results
        for item in results:

            # Each individual result must be parsed
            for key, value in item.items():
                # print(key, value)
                # print(person.items())
                # print((str(key), str(value)) in person.items())
                if ((str(key), str(value)) in person.items()):
                    # print("not getting here")
                    # print("Hit the if")
                    continue
                else:
                    flag = False
                    break

        if (flag == True):
            dnaMatch = person["name"]
            # print(person["name"])
            break
        else:
            dnaMatch = "No match"

    print(dnaMatch)

# Search the string with a regular expression. Using string interpolation (formatted strings) to get my variable in
# This tells it to search the string for the item in question and match one or more occurrances
# I got the idea from the discord searched for help with regex and ended up here https://stackoverflow.com/questions/61131768/how-to-count-consecutive-repetitions-of-a-substring-in-a-string
# and here https://regex101.com/


def searchString(whatToSearchFor, dnaToSearch):
    totals = re.findall(rf'(?:{whatToSearchFor})+', dnaToSearch)
    # print(len(totals))
    if (len(totals) == 0):
        return 0
    else:
        largest = max(totals)
        # print(len(largest) // len(whatToSearchFor))
        return len(largest) // len(whatToSearchFor)  # integer division //


# call main
if __name__ == "__main__":
    main()
