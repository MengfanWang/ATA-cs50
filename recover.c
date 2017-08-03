#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover\n");
        return 1;
    }
    
    char *infile = argv[1];
    // open input file 
    FILE *raw_file = fopen(infile, "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    // define buffer array in hexadecimal with size of 512 since one block is 512 byte
    unsigned char buffer[512];
    // output file variable img
    FILE *img = NULL;
    // check if already find an img
    int findimg = 0;
    // array in char to store filename
    char filename[8];
    int j = 0;
    
    // iterate reading each blocks until hits to the end of file which block size is not 512. fread will return the number of items of 512 size
    while(fread(buffer, 512, 1, raw_file) == 1)
    {
        // read a blocker
        fread(buffer, 512, 1, raw_file);
        // check if the blocker is the header of img
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // check if already find one img then close current file since it is the header of another img
            if(findimg == 1)
            {
                fclose(img);
            }
            else
            {
                findimg = 1;
            }
            // create an output file and open it
            sprintf(filename, "%03i.jpg", j);
            img = fopen(filename, "w");
            j++;
        }
        // write block into output file only when find the img
        if(findimg == 1)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    
    fclose(img);
    fclose(raw_file);
}