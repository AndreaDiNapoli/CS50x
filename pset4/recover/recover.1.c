#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <strings.h>

typedef uint8_t BYTE;

//Prototype for check_jpg function
bool check_jpg (char *block[]);
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

    char *buffer[BLOCKSIZE];
    int counter = 0;
    char *filename = "000.jpg";
    FILE *output = fopen(filename, "w");
    while (fread(buffer, sizeof(BYTE), BLOCKSIZE, input) == BLOCKSIZE)
    {
        if (check_jpg(buffer) == 0)
        {

            fclose(input);
            counter++;
            sprintf(filename, "%03i.jpg", counter);
            output = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, output);
        }
        else
        {
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, output);
        }
    }
    fclose(output);
    fclose(input);
    return 0;
}

bool check_jpg (char *block[BLOCKSIZE])
{
    if (strcasecmp(block[0], "0xff") == 0 && strcasecmp(block[1], "0xd8") == 0 && strcasecmp(block[2], "0xff") == 0 && strcasecmp(block[3], "0xff") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}