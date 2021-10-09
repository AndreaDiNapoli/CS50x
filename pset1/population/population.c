#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Welcome message
    printf("Welcome to the official llamas growth population calculator.\n");
    printf("You will be asked to set how many llamas do you have and the desired number of llamas you want.\n");
    printf("The calculator will tell you how many years of loving care are needed to get your llamas!\n\n");

    // Prompt for start size
    int s;
    do
    {
        s = get_int("Set the starting population number: ");
    }
    while (s < 9);

    // Prompt for end size
    int e;
    do
    {
        e = get_int("Set the desired population number: ");
    }
    while (e < s);

    //Calculate number of years until we reach threshold
    int born;
    int dead;
    int llamas = s;
    int years = 0;

    while (llamas < e)
    {
        born = (float) llamas / 3;
        dead = (float) llamas / 4;
        llamas = llamas + born - dead;
        years++;
    }

    //Print number of years
    printf("Years: %i", years);
}