#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Ask the user for a text to evaluate
    string text = get_string("Text: ");

    //Value counts
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //printf("%i letter(s)\n", letters);
    //printf("%i word(s)\n", words);
    //printf("%i sentence(s)\n", sentences);

    //Calculating the Coleman-Liau index
    float l = (letters * 100) / (float)words;
    float s = (sentences * 100) / (float)words;
    int cl_index = round(0.0588 * l - 0.296 * s - 15.8);

    //Printout the grade value
    if (cl_index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (cl_index >= 16)
    {
        printf("Grade 16+\n");
    }
    if (cl_index > 1 && cl_index < 16)
    {
        printf("Grade %i\n", cl_index);
    }

}







//Letter count function
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            letters++;
        }
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters++;
        }
        else
        {
        }
    }
    return letters;
}

//Words count function
int count_words(string text)
{
    int words = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
        else
        {
        }
    }
    if (words != 0)
    {
        words++;
    }
    return words;
}

//Sentences count function
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        else
        {
        }
    }
    return sentences;
}