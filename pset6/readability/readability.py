def main():
    text = input("Text: ")

    # L is the average number of letters per 100 wornds in text
    L = (count_letters(text) / count_words(text)) * 100
    print(count_letters(text))
    print(count_words(text))
    print(L)

    # S is the average number of sentences per 100 words in text
    S = (count_sentences(text) / count_words(text)) * 100
    print(count_sentences(text))
    print(S)
    
    # the coleman-liau index is computed using the formula:
    index = round(0.0588 * L - 0.296 * S - 15.8)
    print(index)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# function for counting letters in a text


def count_letters(text):
    letters_counter = 0
    for character in text:
        if character.isalpha() is True:
            letters_counter += 1
    return letters_counter

# function for counting the words in a text


def count_words(text):
    words_counter = len(text.split())
    return words_counter

# function for counting the sentences in a text


def count_sentences(text):
    sentences_counter = 0
    
    punctuation = ['.', '!', '?']
    for character in text:
        if character in punctuation:
            sentences_counter += 1
    return sentences_counter


main()