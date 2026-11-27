#include <stdio.h>

#define MAX_LENGTH 500

int main(void)
{
    char text[MAX_LENGTH];
    int vowels = 0;
    int consonants = 0;
    int index;

    printf("Enter a line of text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        printf("Could not read the text.\n");
        return 1;
    }

    for (index = 0; text[index] != '\0' && text[index] != '\n'; index++)
    {
        char letter = text[index];

        if (letter >= 'A' && letter <= 'Z')
            letter = (char)(letter - 'A' + 'a');

        if (letter >= 'a' && letter <= 'z')
        {
            if (letter == 'a' || letter == 'e' || letter == 'i' ||
                letter == 'o' || letter == 'u')
                vowels++;
            else
                consonants++;
        }
    }

    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}
