#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
/*
 * Make a Caesar cipher
 * takes the key to use for shifting as an argument
 */

int main (int argc, string argv[])
{
    int     key;
    string  plainText;

// Make sure that we only have 1 argument (which should be the key)
    if (!(argc == 2))
    {
        if (argc == 1)
            printf ("Missing 'key' argument.\n");
        else
            printf ("Too many arguments.\n");

        return 1;
    }

// Make sure key is between 0 and 25 (for the 26 letters of the alphabet)
    key = atoi (argv[1]) % 26;
    plainText = GetString ();

// Cycle through the string and add the key to encrypt the message
// formula is c(i) = p(i) + k %26 (add ASCII value of a to shift values)
    for (int i = 0; i < strlen (plainText); i++)
    {
        if (isalpha (plainText[i]))
        {
            if (islower (plainText[i]))
                printf("%c", (((plainText[i] - 'a') + key) % 26) + 'a');
            else if (isupper (plainText[i]))
                printf("%c", (((plainText[i] - 'A') + key) % 26) + 'A');
        }
        else
            printf ("%c", plainText[i]);
    }

    printf ("\n");
}
