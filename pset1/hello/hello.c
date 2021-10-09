#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask user name and prompt a personalized greeting
    string answer = get_string("What's your name, my friend?");
    printf("hello, %s!\nPleased to meet you.\n", answer);
}