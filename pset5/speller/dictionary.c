// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of letters in hash function (Must also change N when changing this)
const unsigned int L = 3;

// Number of buckets in hash table (Dependent on L)
const unsigned int N = 21952;

// Hash table
node *table[N];

// size of dictionary (in words) counter
unsigned int sizeOfDict = 1;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Copy word as lower-case. Calloc initializes values to 0.
    char checkWord[strlen(word)];

    for (int i = 0; i <= strlen(word); i++)
    {
        checkWord[i] = tolower(word[i]);
    }

    // Hash word to return index value
    unsigned int checkIndex = hash(checkWord);

    // Initialise cursor & head, and point to that index's pointer
    node *cursor = table[checkIndex];

    // Traverse linked list at that index location and check if word is present, if so, tidy up and return true
    while (cursor != NULL)
    {

        if (strcasecmp(checkWord, cursor->word) == 0)
        {
            return true;
        }

        else
        {
            cursor = cursor->next;
        }
    }

    // In event no word found, tidy up and return false.
    return false;
}

// Hashes word to a number
unsigned int hash(const char *wordToCheck)
{
    // Create index points of first three letters, checking for nul and apostrophe chars
    unsigned int letterIndex[L];
    unsigned int n;

    // Create variable n based on length of word
    if (strlen(wordToCheck) < L)
    {
        n = strlen(wordToCheck);
    }
    else
    {
        n = L;
    }

    for (int i = 0; i < n; i++)
    {
        if (wordToCheck[i] == '\'')
        {
            letterIndex[i] = 27;
        }
        else
        {
            letterIndex[i] = wordToCheck[i] - 97;
        }
    }

    if (n < L)
    {
        while (n < L)
        {
            letterIndex[n] = 26;
            n++;
        }
    }

    // Apply hash algorithm
    unsigned int hashed = 0;
    for (int i = 0; i < L; i++)
    {
        hashed = hashed + pow(letterIndex[i],L - i);
    }

    return hashed;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // Open dictionary file and check for validity
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Dictionary could not be loaded into memory.\n");
        fclose(dict);
        return false;
    }


    // initialize nextWord string. Claloc initializes values to 0
    char nextWord[LENGTH + 1];

    // Scan next word into hash table
    while (fscanf(dict, "%s", nextWord) != EOF)
    {
        // create new node and copy new word
        node *newNode = calloc(1, sizeof(node));
        if (newNode == NULL)
        {
            printf("Not enough memory to load next work from dictionary.");
            return false;
        }

        strcpy(newNode->word, nextWord);
        newNode->next = NULL;

        // hash word
        unsigned int wordHash = hash(nextWord);

        // insert node into hash table
        newNode->next = table[wordHash];
        table[wordHash] = newNode;

        // update size counter
        sizeOfDict++;

        newNode = NULL;
        free(newNode);

    }

    // Close dict
    fclose(dict);

    // Return true
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return sizeOfDict - 1;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    // Initialise cursor pointer and hammer pointer
    node *cursor = NULL;
    node *hammer = NULL;

    // Iterate over entire table
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        hammer = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(hammer);
            hammer = cursor;
        }

    }

    // Return true
    return true;

}
