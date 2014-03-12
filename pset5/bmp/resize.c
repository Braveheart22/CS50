/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP piece by piece
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize SCALE inFile outFile\n");
        return 1;
    }

    // remember filenames
    int scale = atoi (argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
/*
    Need to update  file size   - bf.bfSize
                    image size  - bi.biSizeImage
                    width       - bi.biWidth (does NOT include padding)
                    height      - bi.biHeight
*/
    long originalWidth = bi.biWidth;
    long originalHeight = bi.biHeight;

    bi.biWidth = bi.biWidth * scale;
    bi.biHeight = bi.biHeight * scale;
    bf.bfSize = bf.bfSize * scale;
    bi.biSizeImage = bi.biSizeImage * scale;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int originalPadding =  (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int rowLength = bi.biWidth * scale;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(originalHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        RGBTRIPLE entireRow[rowLength];
        int pixels;
        for (int j = 0, columnNumber = 0; j < originalWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int k = 0; k < scale; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                /*write the triple to an array so we can duplicate the entire row*/
                entireRow[columnNumber] = triple;
                columnNumber ++;
            }
            pixels = columnNumber;
        }
        // skip over padding, if any
        // This would be the padding in the ORIGINAL file
        fseek(inptr, originalPadding, SEEK_CUR);
        
        // Add the padding for the first line we just copied, if necessary
        for (int j = 0; j < newPadding; j++)
        {
            fputc(0x00, outptr);
        }        

        // Copy each line we just created to scale vertically
        for (int j = 0; j < (scale - 1); j++)
        {
            for (int k = 0; k < pixels; k++)
            {
                fwrite(&entireRow[k], sizeof(RGBTRIPLE), 1, outptr);        
            }

            // add padding to new lines, if necessary
            for (int l = 0; l < newPadding; l++)
            {
                fputc(0x00, outptr);
            }        
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
