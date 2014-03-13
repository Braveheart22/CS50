/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    BYTE buffer[512];
    /* TODO
    Open card file (card.raw)
    repeat until end of file
        read 512 bytes into a buffer
        start of new jpg?
            yes -> ...close old, open new
            no  -> ...write data
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
    
    int counter = 0;
    // read 512 bytes of data
    while (fread(&buffer, 512, 1, recoverThis) != 0)
    {
        //check if the first 8 bytes are 0xff 0xd8 0xff 0xe0 or 0xff 0xd8 0xff 0xe1
        if (buffer[0] == 0xff && buffer [1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            char file[7];
            sprintf(file, "%03d.jpg", counter);
            recovered = fopen(file, "r");
            
            printf ("Start of new jpg %03d.\n", counter);
            counter++;
        }
        
        // write data to new jpg file
//        fwrite(&buffer, 512, 1, recoveredFile);

            
    };


   
}
