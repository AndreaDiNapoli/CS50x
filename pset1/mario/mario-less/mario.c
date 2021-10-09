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

    // Build the piramid
    for (int y = 0; y < height; y++)
    {
        for (int space = height - 1; space > y ; space--)
        {
            printf(" ");
        }
        for (int x = 0; x <= y; x++)
        {
            printf("#");
        }
        printf("\n");
    }
}