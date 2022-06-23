#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    
    // L is the average number of letters per 100 words in the text //
    float L = (float) count_letters(text) / (float) count_words(text) * 100;
    
    // S is the average number of sentences per 100 words in the text //
    float S = (float) count_sentences(text) / (float) count_words(text) * 100;

    // the Coleman-Liau index is computed using the formula:
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// function for counting letters //

int count_letters(string text)
{
    int letters_counter = 0;

    for (int i = 0, n = strlen(text); i < n; i++) // n is the overall number of characters
    {
        if (isalpha(text[i]) != 0)
        {
            letters_counter++;
        }
    }

    return letters_counter;
}

// function for counting words //

int count_words(string text)
{
    int words_counter = 0;
    bool first_letter = false;

    for (int i = 0; first_letter != true; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            words_counter++;
            first_letter = true;
        }
    }

    for (int i = 0, n = strlen(text); i < n; i++) // n is the overall number of characters + null character
    {
        if (text[i] == ' ' && isalpha(text[i + 1]) != 0)
        {
            words_counter++;
        }
        
        // in case there's a word with a quotation mark before it
        else if (text[i] == ' ' && text[i + 1] == '"' && isalpha(text[i + 2]) != 0) 
        {
            words_counter++;
        }
    }

    return words_counter;
}

// function for counting sentences //

int count_sentences(string text)
{
    int sentences_counter = 0;

    for (int i = 0, n = strlen(text); i < n; i++) // n is the overall number of characters
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences_counter++;
        }
    }

    return sentences_counter;
}