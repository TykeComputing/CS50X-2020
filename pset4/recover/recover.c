#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define type BYTE
typedef uint8_t BYTE;

// prototype functions
void recoverblocks(BYTE buffer[], int *blocknum, int *filenum, FILE *input, FILE *image);

int main(int argc, char *argv[])
{

    // check for one command-line argument
    if (argc != 2)
    {
        printf("Correct usage: ./recover filename.raw");
        return 1;
    }

    // check for validity of command-line argument

    // open memory card
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fclose(f);
        printf("Could not open file");
        return 2;
    }

    // allocate 512 byte buffer array
    BYTE *buffer = malloc(512);

    // check pointer to buffer array does not return null
    if (buffer == NULL)
    {
        printf("Memory error in buffer.");
        fclose(f);
        free(buffer);
        return 3;
    }

    // set currentblock variable to track current block of 512 bytes in memory card
    int currentblock = 0;

    // set currentfile variable to track current file
    int currentfile = 0;
    char *filename = "000.jpg";

    // write first byte to buffer
    fread(buffer, 512, 1, f);

    // create first jpg
    FILE *image = fopen(filename, "w");
    if (image == NULL)
    {
        printf("Not enough memory to create image.");
        fclose(image);
        fclose(f);
        free(buffer);
        return 4;
    }

    // recoverblocks
    recoverblocks(buffer, &currentblock, &currentfile, f, image);

    //  close file
    fclose(f);

    // free allocated memory
    free(buffer);
}

// recoverblocks function
void recoverblocks(BYTE buffer[], int *blocknum, int *filenum, FILE *input, FILE *image)
{
    // set base case if last block
    if (feof(input))
    {
        // close current file and exit
        fclose(image);
        return;
    }

    // check if new jpg
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        //check if not first jpg and close current file
        if (*filenum != 0)
        {
            fclose(image);

            // update currentfile variable and open new file
            char *name = malloc(10);
            sprintf(name, "%03i.jpg", *filenum);
            image = fopen(name, "w");
            *filenum += 1;
            free(name);

            // check new image pointer does not point to NULL
            if (image == NULL)
            {
                printf("Not enough memory to create image.");
                fclose(image);
                fclose(input);
                free(buffer);
                return;
            }

        }
        else if (*filenum == 0)
        {
            *filenum += 1;
        }
    }

    // write block in buffer to current file if jpeg has been detected
    if (*filenum != 0)
    {
        fwrite(buffer, 512, 1, image);
    }

    // write next block to buffer and recurse
    if (!feof(input))
    {
        fread(buffer, 512, 1, input);
        *blocknum += 1;
        recoverblocks(buffer, blocknum, filenum, input, image);
    }
    return;
}