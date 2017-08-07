/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// define a struct node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

char word[LENGTH + 1];
unsigned int counter = 0;
node *hashtable[26];
bool isload = false;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    char *word_lower = malloc(sizeof(word));
    strcpy(word_lower, word);
    for(int i=0; i<strlen(word); i++)
    {
        word_lower[i] = tolower(word[i]);
    }
    
    int i = word_lower[0] - 'a';
    node *check = hashtable[i];
    while(check != NULL)
    {
        if(strcmp(check->word, word_lower) == 0)
        {
            return true;
        }
        else
        {
            check = check->next;
        }
    }
    free(word_lower);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    while(fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        int index = word[0] - 'a';
        new_node->next = hashtable[index];
        hashtable[index] = new_node; 
        counter++;
    }
    fclose(file);
    isload = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if(isload == true)
    {
        return counter;
    }
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    node *temp;
    for(int i=0; i<26; i++)
    {
        while(hashtable[i] != NULL)
        {
            temp = hashtable[i];
            hashtable[i] = hashtable[i]->next;
            free(temp);
        }    
    }
    isload = false;
    return true;
}
