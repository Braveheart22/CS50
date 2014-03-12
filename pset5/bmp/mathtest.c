#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    for (int i = 0; i < 32; i++)
    {
        int num = (4 - (i * 3) % 4) % 4;
        printf ("%i: %i\n", i, num);
    }
}
