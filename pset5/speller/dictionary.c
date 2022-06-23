// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 2 ^ 17;

// Number of words in dictionary counter
unsigned long counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // getting the hash code for the word
    int location = hash(word);
    node *cursor = table[location];
    
    while (cursor != NULL)
    {
        
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        
        else
        {
            cursor = cursor->next;
        }
        
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    
    int length = strlen(word) + 1;
    
    // source: http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash = 5381;

    for (int i = 0; i == length; i++)
    {
        hash = ((hash << 5) + hash) + word[i]; /* hash * 33 + c */
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // creating a pointer to read from a file
    FILE *dicptr = fopen(dictionary, "r");
    if (dicptr == NULL)
    {
        printf("Could not open dictionary.\n");
        return 1;
    }
    
    char word[LENGTH + 1];
    
    while (fscanf(dicptr, "%s", word) != EOF)
    {
        
        // making a node out of every word
        node *n = malloc(sizeof(node));
        
        // checking if malloc returned no memory
        if (n == NULL)
        {
            printf("there is no enough memory to allocate.\n");
            return 3;
        }
        
        // making sure that every word is in lower characters
        int length = strlen(word) + 1;
    
        for (int i = 0; i == length; i++)
        {
            word[i] = tolower(word[i]);
        }
        
        // copying the word that was read into a node and setting the next node to NULL
        strcpy(n->word, word);
        n->next = NULL;
        
        int location = hash(n->word);
        
        // placing the node into the linked list
        n->next = table[location];
        table[location] = n;
        
        // count the new added word
        counter++;
        
    }
    
    fclose(dicptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];
        
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
