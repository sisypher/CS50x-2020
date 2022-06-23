#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // prompts user for credit card number and validates it as a non-negative

    long ccnum; // credit card number

    do
    {
        ccnum = get_long("Number: ");
    }
    while (ccnum <= 0);

    // counts the number of digits
    long validation = ccnum;
    int digitscount = 0;

    while (validation > 0)
    {
        validation /= 10;
        digitscount++;
    }

    // checks if the number is shorter than 13 or longer than 16
    if (digitscount != 13 && digitscount != 15 && digitscount != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // CHECKSUM //
    // FIRST STEP //
    int sum = 0;
    for (long cc = ccnum; cc > 0; cc /= 100)
    {
        int digit = (cc / 10) % 10;

        if (digit * 2 >= 10)
        {
            sum += (digit * 2) % 10 + ((digit * 2) / 10) % 10;
        }

        else
        {
            sum += digit * 2;
        }
    }

    // SECOND STEP //
    for (long cc = ccnum; cc > 0; cc /= 100)
    {
        int digit = cc % 10;
        sum += digit;
    }

    // Validation for Credit Cards //

    // checking if it's a valid card
    if (sum % 10 == 0)
    {
        // gets the first two digits of the credit card number
        long twodigits = ccnum;

        while (twodigits >= 100)
        {
            twodigits /= 10;
        }

        // checking if it's AMEX
        if (digitscount == 15)
        {

            if (twodigits == 34 || twodigits == 37)
            {
                printf("AMEX\n");
            }

            else
            {
                printf("INVALID\n");
            }
        }

        // checking if it's MASTERCARD or VISA
        else if (digitscount == 16)
        {
            if (twodigits >= 51 && twodigits <= 55)
            {
                printf("MASTERCARD\n");
            }
            else if (twodigits < 50 && twodigits > 39)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // checking if it's VISA
        else if (digitscount == 13)
        {
            if (twodigits < 50 && twodigits > 39)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }

    else
    {
        printf("INVALID\n");
    }

}