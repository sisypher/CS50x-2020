#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


// In a substitution cipher, we “encrypt” (i.e., conceal in a reversible way) a message by replacing every letter with another letter.
// To do so, we use a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when we encrypt it
// To “decrypt” the message, the receiver of the message would need to know the key, so that they can reverse the process:
// translating the encrypt text (generally called ciphertext) back into the original message (generally called plaintext).


int main(int argc, string argv[])
{
    // checking the number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


    string key = argv[1];

    // checking the validation of the key
    int nofc = 0; // number of characters
    bool is_not_alpha = false;

    for (int i = 0; i < 26; i++)
    {
        
        // counting the number of characters
        if (key[i] != '\0')
        {
            nofc++;
        }

        if (isalpha(key[i]) == 0)
        {
            is_not_alpha = true;
        }
        
    }

    // validating the number of characters in the key
    if (nofc != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // validating that every character of the key is alphabetical
    if (is_not_alpha == true)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    // validating that there is not repeated characters
    for (int i = 0; i < 25; i++)
    {
        key[i] = toupper(key[i]);
        
        for (int j = i + 1; j < 26; j++)
        {
            
            key[j] = toupper(key[j]);
            
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
            
        }
        
    }

    // prompt the user for plaintext
    string plaintext = get_string("plaintext: ");
    char ciphertext[strlen(plaintext)];

    for (int i = 0; i <= strlen(plaintext); i++)
    {
        
        // if the letter in plaintext is lowercase
        if (islower(plaintext[i]) != 0)
        {
            
            // a loop for changing all the key letters from uppercase to lowercase
            for (int j = 0; j <= 25; j++)
            {
                
                if (isupper(key[j]) != 0)
                {
                
                    key[j] = tolower(key[j]);
                
                }
                
            }
            
            // setting the ascii range of alphabet a = 0 to z = 25
            // then finding the key alphabet of the same position as the normal alphabet
            ciphertext[i] = key[plaintext[i] - 97];
            
        }
       
        // if the letter in plaintext is uppercase
        else if (isupper(plaintext[i]) != 0)
        {
            
            // a loop for changing all the key letters from lowercase to uppercase
            for (int j = 0; j <= 25; j++)
            {
                    
                if (islower(key[j]) != 0)
                {
                    
                    key[j] = toupper(key[j]);
                    
                }
        
            }
        
            // setting the ascii range of alphabet a = 0 to z = 25
            // then finding the key alphabet of the same position as the normal alphabet
            ciphertext[i] = key[plaintext[i] - 65];
        
        }
        
        // if it is another character then print it as it is
        else
        {
        
            ciphertext[i] = plaintext[i];
        
        }

    }
    
    printf("ciphertext: %s\n", ciphertext);
    
    return 0;
}