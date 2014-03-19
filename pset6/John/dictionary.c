/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    bool isWord;
    struct node* children[27];
}
node;

node root = {false, {NULL}};
unsigned int wordCount = 0;

//Prototype functions
int charVal (char a);
void freeUp (node* thisNode);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //Iterate through each letter in the word passed in
    node* ptr = &root;
    for (int i = 0; i < strlen(word); i++)
    {
    //go to corresponding element in children
        int place = charVal(word[i]);
        //if element does not exist (NULL) word is mispelled
        if (ptr->children[place] == NULL)
        {
            return false;
        }
        else
        // If the letter already exists point to it, and continue
        {
            ptr = ptr->children[place];
        }
    }
    //once at end of word, check isWord variable
    //True is ok, false is mispelled
    return ptr->isWord;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //Open the dictionary file
    FILE* dict = fopen (dictionary, "r");
    //If we can't open the file
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }

//    printf ("DICTIONARY (%s) is open!\n", dictionary);
    //Cycle through the file, and load the trie
    while (!feof(dict))
    {
        char word[LENGTH + 1];
        fscanf (dict, "%s", word);
        node* ptr = &root;
        // Iterate over the word 1 letter at a time
        for (int i = 0; i < strlen(word); i++)
        {
            int place = charVal(word[i]);
            // If the letter doesn't exist, create it
            if (ptr->children[place] == NULL)
            {
                node* new = malloc (sizeof (node));
                ptr->children[place] = new;
                ptr = new;
            }
            else
            // If the letter already exists point to it, and continue
            {
                ptr = ptr->children[place];
            }
        }
        //The word has been added
        ptr->isWord = true;
        wordCount++;
    }

    //Close the dictionary file
    fclose (dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
//    printf ("Words in the dictionary: %i.\n", wordCount);
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    freeUp (&root);
    return true;
}

int charVal (char a)
{
    if (a == '\'')
         return 26;
    else
        return tolower (a) - 'a';
}

void freeUp (node* thisNode)
{
    for (int i = 0; i < 26; i++)
    {
        if (thisNode->children[i] != NULL)
            freeUp (thisNode->children[i]);
        else
            free (thisNode->children[i]);    
    }
}
