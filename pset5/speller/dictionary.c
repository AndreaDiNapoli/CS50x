// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Global counter to speed up size function
int word_counter = 0;

// Number of buckets in hash table
const unsigned int N = 5381;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false (CASE - INSENSITIVE)
bool check(const char *word)
{
    int h = hash(word); //Hash the word
    //Loop for every word store in the hashnumber linked list
    for (node *tmp = table[h]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number (hahs inspired by the djb2 algorythm, by dan bernstein)
unsigned int hash(const char *word)
{

    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);
    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *loaded_dictionary = fopen(dictionary, "r");
    if (loaded_dictionary == NULL)
    {
        return false;
    }

    //Read word after word from the file until the end
    char buffer[LENGTH + 1];
    while (fscanf(loaded_dictionary, "%s", buffer) != EOF)
    {
        //Allocate space for a node and check for error
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            exit(1);
        }
        //Copy the word in the node
        strcpy(n->word, buffer);
        n->next = NULL;
        //Hash the word
        int h = hash(n->word);
        //Insert the node in the appropriate linked list
        if (table[h] == NULL)
        {
            table[h] = n;
        }
        else
        {
            n->next = table[h];
            table[h] = n;
        }
        word_counter++;
    }
    fclose(loaded_dictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Loop for every linked list in the hash table
    for (int i = 0; i < N; i++)
    {
        // Clean every node of the linked list
        while (table[i] != NULL)
        {
            node *tmp = table[i]-> next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
