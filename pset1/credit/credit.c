#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

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

    printf("%lo\n", card);

    //Luhn's algorithm
    //Count card lenght
    int l = 0;
    long copycard = card;
    while ( copycard > 0)
    {
        copycard = copycard/10;
        l++;
    }

    // Check if length is valid
    if (l != 13 && l != 15 && l != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // Calculate checksum
    int s1 = 0;
    int s2 = 0;
    long cc2 = card;
    int total = 0;
    int m1;
    int m2;
    int d1s2;
    int d2s2;

    do
    {
        m1 = cc2 % 10;
        cc2 = cc2 / 10;
        s1 = s1 + m1;
        // Remove second last digit
        m2 = cc2 % 10;
        cc2 = cc2 / 10;
        // Double second last digit and add digits to sum2
        m2 = m2 * 2;
        d1s2 = m2 % 10;
        d2s2 = m2 / 10;
        s2 = s2 + d1s2 + d2s2;
    }
    while (cc2 > 0);

    // Check Luhn Algorithm
    if (total % 10 != 0)
    {
        printf("INVALID\n");
    }

    // Extract the first two digits
    long cc3 = card;
    do
    {
        cc3 = cc3 / 10;
    }
    while (cc3 > 100);
    int start = cc3;

    //Check card provider
    if (start == 51 || start == 52 || start == 53 || start == 54 || start == 55)
    {
    printf("MASTERCARD\n");
    }
    else if (start == 34 || start == 37)
    {
    printf("AMEX\n");
    }
    else if ((start / 10) == 4)
    {
    printf("VISA\n");
    }
    else
    {
    printf("INVALID\n");
    }
}