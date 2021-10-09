#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask for piramid height
    int height;
    do
    {
        height = get_int("Set the piramid height: ");
    }
    while (height <= 0 || height > 8);

    // Set the piramid height
    for (int y = 0; y < height; y++)
    {
        //Buil the first half of the piramid
        for (int space = height - 1; space > y ; space--)
        {
            printf(" ");
        }
        for (int x = 0; x <= y; x++)
        {
            printf("#");
        }

        //Set the gap
        printf("  ");

        //Built the second half of the piramid
        for (int x = 0; x <= (y); x++)
        {
            printf("#");
        }
        printf("\n");
    }
}