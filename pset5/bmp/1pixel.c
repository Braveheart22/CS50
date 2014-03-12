#include <stdio.h>
 
int main(void){
 
FILE *f;
int filesize = 54 + 3*1*1;
 
unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
unsigned char bmpcontent[6] = {255,0,0};
unsigned char bmppad[3] = {0,0,0};
 
/* Construct header with filesize part */
        bmpfileheader[ 2] = (unsigned char)(filesize    );
        bmpfileheader[ 3] = (unsigned char)(filesize += 8);
        bmpfileheader[ 4] = (unsigned char)(filesize += 16);
        bmpfileheader[ 5] = (unsigned char)(filesize += 24);
 
        /* Construct header with width and height part */
        bmpinfoheader[ 4] = (unsigned char)(        1    );
        bmpinfoheader[ 8] = (unsigned char)(       1    );
 
        f = fopen("1.bmp","wb");
        fwrite(bmpfileheader,1,14,f);
        fwrite(bmpinfoheader,1,40,f);
        fwrite(bmpcontent,3,6,f);
        fwrite(bmppad,1,3,f);
 
        fclose(f);
return 1;
}
