#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Caesar used to “encrypt” (i.e., conceal in a reversible way) confidential messages by shifting each letter therein by some number of places. //

int main(int argc, string argv[])
{
    
    // checking if there's only 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }
    
    int key = atoi(argv[1]);
    
    
    // checking that the key is non-negative
    if (key < 0)
    {
        printf("Usage: ./caesar key\n");

        return 1;
    }
    
    
    else
    {
        // checking if the key is not an integer (if the key contains char other than numeric characters)
        bool not_an_int = false;

        for (int j = 0; argv[1][j] != '\0'; j++)
        {
            if (isalpha(argv[1][j]) != 0)
            {
                not_an_int = true;
            }
        }

        // in case the key is not an int
        if (not_an_int == true)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // in case the key is an int
        string plaintext = get_string("plaintext: ");
        char ciphertext[strlen(plaintext)];

        // a loop to go thrpugh every character of the plaintext
        for (int i = 0; i <= strlen(plaintext); i++)
        {

            // checking if the character is alpahbatical
            if (isalpha(plaintext[i]) != 0)
            {

                // checking if it is a lowercase alphabet
                if (islower(plaintext[i]) != 0)
                {

                    // checking if the key bigger than 'z' = 122
                    if (plaintext[i] + key > 122)
                    {

                        //formula: ci = (pi + k) % 26
                        ciphertext[i] = 97 + ((plaintext[i] - 97 + key) % 26);
                    }

                    else
                    {
                        ciphertext[i] = plaintext[i] + key;
                    }

                }

                // checking if it is an uppercase alphabet
                else if (isupper(plaintext[i]) != 0)
                {
                    // checking if the key bigger than 'Z' = 90
                    if (plaintext[i] + key > 90)
                    {

                        //formula: ci = (pi + k) % 26
                        ciphertext[i] = 65 + ((plaintext[i] - 65 + key) % 26);
                    }

                    else
                    {
                        ciphertext[i] = plaintext[i] + key;
                    }

                }
            
            }
            
            // if the character anything other than alphabetical
            else
            {
                ciphertext[i] = plaintext[i];
            }

        }
        
        printf("ciphertext: %s\n", ciphertext);

        return 0;

    }
}