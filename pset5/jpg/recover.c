/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    /* TODO
    Open card file (card.raw)
    repeat until end of file
        read 512 bytes into a buffer
        start of new jpg?
            yes -> ...
            no  -> ...
        already found a jpg?
            no  -> ...
            yes -> ...
        close last jpg
        close card file
        
    Name the jpg file 000.jpg, 001.jpg...
    use sprintf (title, "%d.jpg", 2);
    Figure out how to add leading zeros. (something like %00d.jpg?)
    */
    
    FILE* recoverThis = fopen("card.raw", "r");
    if (recoverThis == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
   
}
