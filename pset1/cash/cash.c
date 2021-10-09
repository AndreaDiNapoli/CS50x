#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Declare the main variables
    int coins = 0;
    float input;
    //Ask how much change is to do, round it to cents and translate it to an integer
    do
    {
        input = get_float("Change owed: ");
    }
    while (input < 0);

    int change = round(input * 100);

    //Set the value of the coins
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    //Check if quarters are needed, how many and go on with the change left
    while (change >= quarter)
    {
        change = change - quarter;
        coins++;
    }

    //Check if dimes are needed, how many and go on with the change left
    while (change >= dime)
    {
        change = change - dime;
        coins++;
    }

    //Check if nickels are needed, how many and go on with the change left
    while (change >= nickel)
    {
        change = change - nickel;
        coins++;
    }

    //Check if pennies are needed, how many and go on with the change left
    while (change >= penny)
    {
        change = change - penny;
        coins++;
    }

    printf("%i\n", coins);

}