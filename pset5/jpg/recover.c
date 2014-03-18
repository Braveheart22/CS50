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
    int counter = 0;
    FILE* recoverThis = fopen("card.raw", "r");
    FILE* recovered = NULL;
    
    if (recoverThis == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
    
    // read 512 bytes of data
    while (fread (&buffer, 512, 1, recoverThis) != 0)
    {
        //check if the first 8 bytes are 0xff 0xd8 0xff 0xe0 or 0xff 0xd8 0xff 0xe1
        if (buffer[0] == 0xff && buffer [1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
        //close file if one is open (we're starting a new one)
            if (recovered != NULL)
                fclose (recovered);

            char file[8];
            sprintf(file, "%03d.jpg", counter);
            recovered = fopen(file, "w");

            if (recovered == NULL)
            {
                printf("Could not open %s.\n", file);
                return 1;
            }
        // Write the "header" information
            fwrite(&buffer, 512, 1, recovered);
            counter++;
        }
        else
        {
        // write data to jpg file
            if (recovered != NULL)
            {
                fwrite(&buffer, 512, 1, recovered);
            }
        }
    }

// Close any open files
    fclose (recovered);
    fclose (recoverThis);   
}
