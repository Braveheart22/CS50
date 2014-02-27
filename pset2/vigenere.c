#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
/*
 * Make a Viginere cipher
 * takes an alpha key to use for shifting as an argument
 */

int main (int argc, string argv[])
{
    string  key;
    string  plainText;
    int     nonAlpha = 0;

// Make sure that we only have 1 argument (which should be the key)
    if (!(argc == 2))
    {
        if (argc == 1)
            printf ("Missing 'key' argument.\n");
        else
            printf ("Too many arguments.\n");
        return 1;
    }

    key = argv[1];
    for (int i = 0; key[i]; i++)
    {
        key[i] = tolower (key[i]);
    }
// Make sure key is an alpha key
    for (int i = 0; key[i]; i++)
    {
        if (!(isalpha (key[i])))
        {
            printf ("Key must be all alpha characters.\n");
            return 1;
        }
    }
    plainText = GetString ();
// Cycle through the string and add the key to encrypt the message
// formula is c(i) = p(i) + k %26 (add ASCII value of 'a' to shift values)

    for (int i = 0; i < strlen (plainText); i++)
    {
        if (isalpha (plainText[i]))
        {
            if (islower (plainText[i]))
                printf("%c", (((plainText[i] - 'a') + ((key[((i - nonAlpha) % strlen(key))] - 'a'))) % 26 + 'a'));
            else if (isupper (plainText[i]))
                printf("%c", (((plainText[i] - 'A') + ((key[((i - nonAlpha) % strlen(key))] - 'a'))) % 26 + 'A'));
        }
        else
        {
            printf ("%c", plainText[i]);
            nonAlpha++;
        }
    }

    printf ("\n");
}


