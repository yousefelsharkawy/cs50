// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int words_no = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char words[LENGTH + 1];
    // Initializing the array with null
    for (int I = 0; I < (LENGTH); I++)
    {
        words[I] = '\0';   
    }
    // Converting the array to lowercase
    strcpy(words, word);
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        words[i] = tolower(words[i]);
    }
    // Hashing the input to find where to start checking
    int number = hash(words);
    node *tmp = table[number];
    while (tmp != NULL)
    {
        if (strcmp(tmp -> word, words) == 0)
        {
            return true;
        }
        tmp = tmp -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hashing the input by the first 3 letters of the word
    int n = (word[0] % 97) * 676 + (word[1] % 97) * 26 + (word[2] % 97) * 1;
    return n;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opening the dictionary for reading
    FILE *ptr = fopen(dictionary, "r");
    if (ptr == NULL)
    {
        printf("coudn't open the file\n");
        return 1;
    }
    // Declaring a temporary array to hold words
    char tmp_word[LENGTH + 1];
    // Initializing the array with null values
    for (int i = 0; i < (LENGTH + 1); i++)
    {
        tmp_word[i] = '\0';
    }
    // Reading from the dictionary word by word
    while (fscanf(ptr, "%s", tmp_word) != EOF)
    {
        // Hashing the word0
        int number = hash(tmp_word);
        // Creating a node to contain the word
        node *n = malloc(sizeof(node));
        // Checking we got valid pointer
        if (n == NULL)
        {
            printf("couldn't allocate memory\n");
            return 1;
        }
        // Initializing the node with the values
        strcpy(n -> word, tmp_word);
        n -> next = NULL;
        // Inserting the node to the hashtable
        if (table[number] == NULL)
        {
            table[number] = n;
        }
        else
        {
            n -> next = table[number];
            table[number] = n;
        }
        // Re-initializing the array to take the next value
        for (int j = 0; j < (LENGTH + 1); j++)
        {
            tmp_word[j] = '\0';
        }
        words_no++;
    }
    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return words_no;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Looping on all of the hashtable
    for (int i = 0; i < N; i++)
    {
        // freeing the memory for each element in the array of the pointers
        while (table[i] != NULL)
        {
            node *tmp = table[i] -> next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
