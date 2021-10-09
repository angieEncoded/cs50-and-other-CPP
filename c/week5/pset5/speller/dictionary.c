// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table - change this to 26 to give me each letter
//const unsigned int N = 26;// WORKING WITH ORIGINAL SOLUTION
const unsigned int N = 1000;


// Hash table
node *table[N];

// numberOfWords in the dictionary (only positive int)
unsigned int numberOfWords = 0;
bool fullyLoaded = false;


// Loads dictionary into memory, returning true if successful, else false
// REMEMBER this is just a string. don't get hung up on the pointer aspect
bool load(const char *dictionary)
{

    // Open the file
    FILE *inputFile = fopen(dictionary, "r");
    // Make sure it opened, if not return false
    if (inputFile == NULL)
    {
        return false;
    }

    // Set up a buffer of length
    // Remember that not everything has to be a pointer....
    // This is just an array of characters
    char buffer[LENGTH + 1]; // add one for a newline

    // I had tried this initially from page 367 in the stephen Kochan book but it did not put the data as expected.
    // while(fgets(buffer, LENGTH, inputFile) != NULL){
    while (fscanf(inputFile, "%s", buffer) != EOF)
    {
        int locationInTable = 0;
        //printf("%s", buffer);

        // send the word into the hash function to determine where it goes
        locationInTable = hash(buffer) % N;

        // Allocate memory for a new node with malloc
        node *n = malloc(sizeof(node));

        // Check that we got the memory
        if (n == NULL)
        {
            return false;
        }

        // Copy the data into the new node and set its pointer to null
        strcpy(n->word, buffer);
        // n->next = NULL;
        n->next = table[locationInTable]; // New node must point at old first node
        table[locationInTable] = n; // table now points at the new node
        numberOfWords++;

        // add the new node to the beginning of the linked list!
        // Get the node at table[locationInTable];
        // point the new node at whatever table[locationInTable] is pointing to
        // point table[locationInTable] at the new node.


        // // if there is no node just insert it. We're the first
        // if (table[locationInTable] == NULL){
        //     table[locationInTable] = n;
        // } else {
        // Otherwise we need to set the pointers appropriately

        // }
    }


    // Clean up after myself
    fclose(inputFile);
    fullyLoaded = true;
    return true;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Outer loop to go down the table - standard for loop
    for (int i = 0; i < N; i++)
    {

        while (table[i] != NULL)
        {
            node *currentNode = table[i]->next;
            free(table[i]);
            table[i] = currentNode;
        }


    }


    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (fullyLoaded)
    {
        return numberOfWords;
    }
    else
    {
        return 0;
    }
}


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get the hash value of the word
    const int location = hash(word) % N;




    // go to that location in the table
    // use the node syntax for loop to iterate and compare each word
    for (node *tmp = table[location]; tmp != NULL; tmp = tmp->next)
    {

        //printf("%s is the word in the location \n", tmp->word);


        if (strcasecmp(word, tmp->word) == 0)
        {

            //printf("%s WAS FOUND TRUE\n", word);

            return true;
            break;
        }
    }


    return false;
}


// Hashes word to a number
// Char star means string
unsigned int hash(const char *word)
{

    // WORKING, BUT SLOW AS ALL GET OUT
    //=============================================
    //printf("%i", charNum);
    // Check the first character in the word against the ascii table
    // 97 through 122
    // Position in the array = ASCII position - 97 gets us where it belongs
    // lol this is my first implementation of hash function. Holy crow,
    // this is embarassing, but I didn't get it from anywhere but my week 1-2 notes on ascii
    // char firstChar = tolower(word[0]);
    // return (int)firstChar - 97;
    //=============================================

    // WORKING AS WELL, BUT THIS TOOK EVEN LONGER THAN ABOVE
    //=============================================
    // Can possibly check the number of characters
    // then 45 buckets with one bucket for each
    // const int number = strlen(word);
    // return number - 1;
    //=============================================




    // I found this one in this stack overflow post
    // It is the djb2 algorithm by Dan Bernstein
    // http://www.cse.yorku.ca/~oz/hash.html
    // https://stackoverflow.com/questions/14409466/simple-hash-functions
    // Times were really close to what the instructors had. With 2k buckets.
    // https://www.reddit.com/r/cs50/comments/eo4zro/good_hash_function_for_speller/
    //=============================================
    int hashAddress = 5381;
    for (int counter = 0; word[counter] != '\0'; counter++)
    {
        // remember to lowercase the letter to make sure it always returns the same
        hashAddress = ((hashAddress << 5) + hashAddress) + tolower(word[counter]);
    }
    return hashAddress;
    //=============================================
    // With this one run a modulo operation when you call the function -
    // the number to modulo is the number of buckets you are using, I used 2k buckets
    // might have been overkill but my eyes are bleeding and it works so... moving on.

}
