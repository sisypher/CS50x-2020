#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompts the user for a number from 1 through 8
    int height = 0;
    
    while (height <= 0 || height >= 9)
    {
        height = get_int("Height: ");
    }
    
    for (int i = 0; i < height; i++)
    {
        // prints spaces before the #
        for (int s = height - i ; s > 1 ; s--)
        {
            printf(" ");
        
        }
        
        // prints the # 
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        printf("\n");

    }
}