# Welp I misunderstood the task and this isn't going to work

  # Send in the DNA in question, and the list of DNA sequences to look for and count
  results = []
   for item in dnaStringsToSearch:
        # Send into the recusive function to count
        number = checkSubString(item, dnaInQuestion)
        # Add to the list if it's not already there
        results.append({item: number})
    print(results)
    # dnaResults = checkSubString(dnaStringsToSearch, dnaInQuestion)

    results = []
    # iterate over the list of candidates
    for person in dnaRecords
      # Check their records against the DNA


def checkSubString(itemToSearchFor, dnaInQuestion):

    # check the string for the substring
    itemLength = len(itemToSearchFor)
    result = dnaInQuestion.find(itemToSearchFor)

    # if it returns -1 it doesn't exist. We are done
    if (result == -1):
        return 0

    # if it returns an index, we chop off the front of the string and send it back into the function
    else:

        newString = dnaInQuestion[result + itemLength:len(dnaInQuestion)]
        # print(newString)
        return 1 + checkSubString(itemToSearchFor, newString)





    # print(dnaInQuestion)
    for item in dnaStringsToSearch:
        getHighestOccurances(0, item, dnaInQuestion)

    # what if I log the indexes they were fo


def getHighestOccurances(itemToSearchFor, dnaInQuestion):

    indexLocations = []

    # sub function to check the string for every instance it exists
    def checkSubString(startingIndex, itemToSearchFor, dnaInQuestion):
        result = dnaInQuestion.find(
            itemToSearchFor, startingIndex, len(dnaInQuestion))
        if (result == -1):
            return

        else:
            indexLocations.append(result)
            checkSubString(0, itemToSearchFor, dnaInQuestion)

    #     # check the string for the substring
    # itemLength = len(itemToSearchFor)
    # result = dnaInQuestion.find(itemToSearchFor)

    # # if it returns -1 it doesn't exist. We are done
    # if (result == -1):
    #     return 0

    # # if it's not = to the 0 index, we don't have a consecutive string
    # if(result != 0):

    #     # if it returns an index and it , we chop off the front of the string and send it back into the function
    # else:

    #     newString = dnaInQuestion[result + itemLength:len(dnaInQuestion)]
    #     # print(newString)
    #     return 1 + checkSubString(itemToSearchFor, newString)


    #     # check the string for the substring
    # itemLength = len(itemToSearchFor)
    # result = dnaInQuestion.find(itemToSearchFor)

    # # if it returns -1 it doesn't exist. We are done
    # if (result == -1):
    #     return 0

    # # if it's not = to the 0 index, we don't have a consecutive string
    # if(result != 0):

    #     # if it returns an index and it , we chop off the front of the string and send it back into the function
    # else:

    #     newString = dnaInQuestion[result + itemLength:len(dnaInQuestion)]
    #     # print(newString)
    #     return 1 + checkSubString(itemToSearchFor, newString)
