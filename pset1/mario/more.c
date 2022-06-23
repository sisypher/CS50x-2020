#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        // this is a loop that prints the space
        for (int s = height - i; s > 0; s--)
        {
            printf(" ");
        }
        // this is a loop that prints the left pyramid
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }

        printf("  "); // this is for the gap between the two pyramids

        // this is a loop that prints the right pyramid
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}