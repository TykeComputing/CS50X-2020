#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//Declare functions
void substitute(char input, int charkey);

int main(int argc, string argv[])
{

    //check for key
    if (argc != 2)
    {
        printf("Error 1: Syntax must be: ./substitution key\n");
        return 1;
    }

    //check length of key
    if (strlen(argv[1]) != 26)
    {
        printf("Error 2: key must contain every letter of the alphabet.\n");
        return 1;
    }

    //check for non-alphabet symbols in key
    for (int i = 0; i < 26; i++)
    {
        if (argv[1][i] < 65 || argv[1][i] > 122)
        {
            printf("Error 3: key must only contain letters from the Roman alphabet.\n");
            return 1;
        }
    }

    //create key array
    int key[26];
    for (int i = 0; i < 26; i++)
    {
        key[i] = ((int)toupper(argv[1][i]) - 65);
    }

    //for loop to check for uniqueness
    int checkarr[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (key[i] == j)
            {
                if (checkarr[j] == 0)
                {
                    checkarr[j] = 1;
                }
                else if (checkarr[j] == 1)
                {
                    printf("You must only use each letter once.\n");
                    return 1;
                }
            }
        }
    }


   //get input text from user
   string plaintext = get_string("plaintext: ");
   int textlen = strlen(plaintext);

   //print ciphertext
   printf("ciphertext: ");

   //iterate over input and return ciphertext
   for (int i = 0; i < textlen; i++)
   {
       int k = (toupper(plaintext[i]) - 65);
       substitute(plaintext[i], key[k]);
   }

   //end on newline
   printf("\n");

}

//define substitute function
void substitute(char input, int charkey)
{
    if (isupper(input))
    {
        printf("%c", (charkey % 26) + 65);
    }
    else if (islower(input))
    {
        printf("%c", (charkey % 26) + 97);
    }
    else
    {
        printf("%c", input);
    }
}