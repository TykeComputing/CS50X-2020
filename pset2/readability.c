#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    //get input from user
    string input = get_string("Please enter the sentence: ");

    //iterate over input, counting total of letters, sentences and words
    int n = strlen(input);
    int letters = 0;
    int sentences = 0;
    int words = 1;

    for (int i = 0; i < n; i++)
    {
        if (input[i] == 46 || input[i] == 63 || input[i] == 33)
        {
            sentences++;
        }
        else if (input[i] == 32)
        {
            words++;
        }
        else if (isalpha(input[i]))
        {
            letters++;
        }

    }

    //convert to L (average letters per 100 words)
    float L = ((float)letters / (float)words) * 100;

    //convert to S (average sentences per 100 words)
    float S = ((float)sentences / (float)words) * 100;

    //run Colemann-Lieu formula to determine grade
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //return suggested grade to user
    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        printf("Grade %.0f\n", index);
        return 0;
    }


}