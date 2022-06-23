#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensuring proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }
    
    // remember filename as infile
    char *infile = argv[1];
    
    // opening infile pointer for reading
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }
    
    BYTE buffer[512];
    unsigned int jpgCounter = 0;
    FILE *img;
    char filename[8];
    double num = 0; // for detecting if it reads a full 1 block of 512 bytes or less.
    
    while (!feof(inptr))
    {
        
        num = fread(buffer, 512, 1, inptr);
        
        // checks if the first 4 bytes of the block is the header of a JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            
            // checks if it is the first JPG
            if (jpgCounter == 0)
            {
                sprintf(filename, "%03i.jpg", jpgCounter);
                img = fopen(filename, "w");
                
                fwrite(buffer, 512, num, img);
                jpgCounter++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpgCounter);
                img = fopen(filename, "w");
                
                fwrite(buffer, 512, num, img);
                jpgCounter++;
            }
        }
        
        // checks if a JPG was already found and continues writing to its file
        else if (jpgCounter != 0)
        {
            fwrite(buffer, 512, num, img);
        }
    
    }
    
    fclose(inptr);
    fclose(img);
    
}
