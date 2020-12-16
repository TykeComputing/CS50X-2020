#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    //Get Number
    long intnumber = get_long("Long Card Number: ");

    //Convert intnumber to a string
    char number[20];
    sprintf(number, "%li", intnumber);

    //Get length of string
    int numberlen = strlen(number);

    //Check numberlen is within range
    if (numberlen < 13 || numberlen > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    //Sum the numbers
    int intsum = 0;

    int a = 0;
    int b = 1;

    if (numberlen == 13 || numberlen == 15)
    {
        a = 1;
        b = 0;
    }

    for (int i = a; i < numberlen; i += 2)
    {

        int numberi = number[i] - 48;
        numberi = numberi * 2;

        if (numberi < 10)
        {
            intsum = intsum + (numberi);
        }

        else if (numberi >= 10)
        {
            intsum = intsum + 1 + (numberi - 10);
        }

        else
        {
            printf("Error");
            return 1;
        }

    }

    for (int i = b; i < numberlen; i += 2)
    {
        intsum = intsum + (number[i] - 48);
    }

    //Convert First two digits of number to an integer
    int startdigits = ((number[0] - 48) * 10) + (number[1] - 48);

    //Check final sum number is 0,
    //compare numberlen to expected length of relevant card-type,
    //if valid, return type, else return invalid
    if (intsum % 10 == 0)
    {
        if (startdigits == 34 || startdigits == 37)
        {
            printf("AMEX\n");
            return 0;
        }

        else if (startdigits > 50 && startdigits < 56 && numberlen == 16)
        {
            printf("MASTERCARD\n");
            return 0;
        }

        else if (startdigits > 39 && startdigits < 50 && (numberlen == 13 || numberlen == 16))
        {
            printf("VISA\n");
            return 0;
        }

        else
        {
            printf("INVALID\n");
            return 0;
        }

    }

    else
    {
        printf("INVALID\n");
        return 0;
    }

}