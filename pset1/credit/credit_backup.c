#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Get from the user the credit cart number to check
    long card;

    printf("Welcome to this credit card validator, based on Luhn's algorithm.\n");
    do
    {
        card = get_long("Card number:  ");
    }
    while(card < 0);

    //Luhn's algorithm

    //Extract single digit
    int digit[15] = {0};
    int counter = 0;
    while (card !=0)
    {
        digit[counter] = card % 10;
        card = card / 10;
        counter++;
    }

    //Store the 16th digit
    int firstnumber = digit[15];

    //Calculate the checksum
    int checksum = 0;
    while (int t = 16; t >= 0; t--)
    {
        if (digit[t]%2 == 0)
        {
           while (digit[t] != 0)
            {
                checksum = + (digit % 10);
                digit[t] = digit / 10;
            }
        }
        else
        {
            digit[t] = digit[i]*2;
            while (digit[t] != 0)
            {
                checksum = + (digit % 10);
                digit[t] = digit / 10;
            }
        }
    }

    //Control validity
    if ((checksum % 10) == 0)
    {
        if(("%i",counter) == 15)
        {
            printf("AMEX\n");
        }
        if(("%i",counter) == 13)
        {
            printf("VISA\n");
        }
        if(("%i",counter) == 16);
        {
            if (firstnumber == 5)
            {
              printf("MASTER\n");
            }
            else
            {
              printf("VISA\n");
            }
        }
    }
    else
    {
    printf("INVALID\n");
    }
}