#include "helpers.h"
#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int myArray[5] = {5, 14, 82, 3, 991};
//    int swaps = 0;
    printf ("Start Array: ");
    for (int i = 0; i < 5; i++)
    {
        printf (", %i", myArray[i]);
    }
    printf ("\n");
    sort (myArray, 5);

/*    do
    {
        swaps = 0;
        for (int i = 0; i < 4; i++)
        {
            if (myArray[i] > myArray[i+1])
            {
                int temp = myArray[i];
                myArray[i] = myArray[i+1];
                myArray[i+1] = temp;
                swaps++;
            }
        }
    }
    while (swaps > 0);
*/
    
    printf ("End Array: ");
    for (int i = 0; i < 5; i++)
    {
        printf (", %i", myArray[i]);
    }
    printf ("\n");
}
