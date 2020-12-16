#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//get key to cipher as a command line argument
int main(int argc, string argv[])
{
    //check a key has been provided
    if (argc != 2)
    {
        printf("Error 1: Syntax must be: ./caeser key\n");
        return 1;
    }

    //check key is numerical
    int n = strlen(argv[1]);
    for (int i = 0; i < n; i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 57)
        {
            printf("Key must be numerical.\n");
            return 1;
        }
    }

    //Convert key to an integer and print
    int key = atoi(argv[1]) % 26;
    printf("Key is: %i\n", key);

    //get plaintext from user
    string plaintext = get_string("plaintext: ");

    //get length of plaintext
    int l = strlen(plaintext);

    printf("ciphertext: ");

    //encode each character and print one at a time, maintaining case
    for (int i = 0; i < l; i++)
    {
        if (plaintext[i] < 65 || plaintext[i] > 122 || (plaintext[i] > 90 && plaintext[i] < 97))
        {
            printf("%c", plaintext[i]);
        }
        else if (plaintext[i] > 64 && plaintext[i] < 91)
        {
            char ccipher = ((((plaintext[i] - 65) + key) % 26) + 65);
            printf("%c", ccipher);
        }
        else if (plaintext[i] > 96 && plaintext[i] < 123)
        {
            char ccipher = ((((plaintext[i] - 97) + key) % 26) + 97);
            printf("%c", ccipher);
        }
        else
        {
            printf("Error 3: unknown");
            return 1;
        }

    }

    //end program with a new line
    printf("\n");
    return 0;


}