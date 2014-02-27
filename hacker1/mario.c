#include <cs50.h>
#include <stdio.h>
/*
 * Itsa Mario: Create the staircase used by Mario to
 * capture the flag using any height between 0 and 23.
 * 1/14/14 JS
 *
 */

int main (void)
{
    int height;
    
    do
    {
        printf ("Enter a height (between 0 and 23): ");
        height = GetInt ();
    }
    while (height < 0 || height > 23);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (height - i) - 1; j++)
        {
            printf (" ");
        }
        
        for (int j = 0; j < i + 1; j++)
        {
            printf ("#");
        }
        
        printf ("  ");

        for (int j = 0; j < i + 1; j++)
        {
            printf ("#");
        }
        
        printf ("\n");
    }
    return 0;

}
