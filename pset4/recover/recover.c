#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <strings.h>

typedef uint8_t BYTE;

const int BLOCKSIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover input.raw\n");
        return 1;
    }

    // Open files and check
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open the file\n");
        return 2;
    }

    //Inizialize variable needed
    //buffer
    BYTE buffer[BLOCKSIZE];
    //counter and filename variable to handle progressive naming
    int counter = 0;
    char filename[8];
    //allocate for output file
    FILE *output = NULL;
    //status check for an open jpg
    bool open_jpg = false;

    //Start reading block after block
    while (fread(buffer, BLOCKSIZE, 1, input) == 1)
    {
        //Check if jpeg header is found at the start of the block
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Check if a jpg is open
            if (open_jpg == true)
            {
                //Close the current image
                fclose(output);
            }
            //Set the appropriate namefile, open the file and update the counter
            sprintf(filename, "%03i.jpg", counter);
            output = fopen(filename, "w");
            counter++;
            open_jpg = true;

            //Write a block into the open file
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, output);
        }
        else
        {
            if (open_jpg == true)
            {
                fwrite(buffer, sizeof(BYTE), BLOCKSIZE, output);
            }
        }
    }
    fclose(input);
    return 0;
}