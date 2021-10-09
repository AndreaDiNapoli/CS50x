#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Chek the argument validity
    if (argc == 2 && isdigit(*argv[1]))
    {
        //Convert the key value into an integer and store into a variable
        int key = atoi(argv[1]);

        //Ask the user for the text to cipher
        string text = get_string("plaintext: ");

        //Print ciper title
        printf("ciphertext: ");

        //Ciper every single char applying the key, till the text is over
        for (int i = 0, l = strlen(text); i < l ; i++)
        {
            //Cipher lowecase letters and print it
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                printf("%c", (((text[i] - 'a') + key) % 26) + 'a');
            }

            //Cipher uppercase letters and print it
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                printf("%c", (((text[i] - 'A') + key) % 26) + 'A');
            }

            //Print other character witouth encrypting
            else
            {
                printf("%c", text[i]);
            }
        }

        //Return the default value
        printf("\n");
        return 0;
    }

    //Print the usare message and return an error value
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
