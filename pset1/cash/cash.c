#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float co; // change owed
    int noc = 0; // number of coins

    // a loop checks that the number isn't negative
    do
    {
        co = get_float("Change owed: ");
    }
    while (co < 0);

    int cents = round(co * 100); // converting from float to integer (from dollars to cents)

    // a loop for counting the number of cents
    do
    {
        if (cents >= 25)
        {
            cents -= 25;
            noc++; // increment the number of cents by 1
        }
        else if (cents >= 10)
        {
            cents -= 10;
            noc++;
        }
        else if (cents >= 5)
        {
            cents -= 5;
            noc++;
        }
        else if (cents >= 1)
        {
            cents -= 1;
            noc++;
        }
    }
    while (cents != 0);
    printf("%i\n", noc);
}
