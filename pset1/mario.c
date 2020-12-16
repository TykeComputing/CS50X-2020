#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get height from user
    int height = get_int("Height: \n");

    //Check height is a positive integer between 1 and 8 inclusive
    for (int h = height; height < 1 || height > 8; h = height)
    {
        height = get_int("Height: \n");
    }

    //Loop printing of pyramid
    for (int i = 0; i < height; i++)
    {

        //print indentation of line
        for (int indent = height - 2; indent >= i; indent--)
        {
            printf(" ");
        }

        //print left pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        //print centre space
        printf("  ");

        //print right pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");

    }

    return 0;

}