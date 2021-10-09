from cs50 import get_string

# Define main function


def main():

    # Get the text to evaulate from the user
    text = get_string("Text: ")

    # Count letters, words and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Calculating the Coleman-Liau index
    l = (letters * 100) / words
    s = (sentences * 100) / words
    cl_index = round(0.0588 * l - 0.296 * s - 15.8)

    # Printout the grade value
    if cl_index < 1:
        print("Before Grade 1")
    elif cl_index > 16:
        print("Grade 16+")
    elif cl_index > 1 or cl_index < 16:
        print(f"Grade {cl_index}")


# Define Letter count function


def count_letters(text):
    letters = 0
    for i in range(len(text)):
        if text[i] >= 'A' and text[i] <= 'Z':
            letters += 1
        elif text[i] >= 'a' and text[i] <= 'z':
            letters += 1
    return letters

# Define Words count function


def count_words(text):
    words = 0
    for i in range(len(text)):
        if text[i] == ' ':
            words += 1
    if words != 0:
        words += 1
    return words

# Define Sentences count function


def count_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            sentences += 1
    return sentences


if __name__ == "__main__":
    main()