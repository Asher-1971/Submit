#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char titles[5][50];
    int copies[5];
    int i, j, vowels, most_copies = 0;
    char letter;

    for (i = 0; i < 5; i++)
    {
        printf("Enter title for book %d: ", i + 1);
        scanf(" %[^\n]", titles[i]);
        printf("Enter number of copies: ");
        scanf("%d", &copies[i]);
    }

    printf("\n%-5s %-30s %-10s %-10s\n", "No.", "Title", "Copies", "Vowels");
    for (i = 0; i < 5; i++)
    {
        vowels = 0;
        for (j = 0; titles[i][j] != '\0'; j++)
        {
            if (tolower((unsigned char)titles[i][j]) == 'a' ||
                tolower((unsigned char)titles[i][j]) == 'e' ||
                tolower((unsigned char)titles[i][j]) == 'i' ||
                tolower((unsigned char)titles[i][j]) == 'o' ||
                tolower((unsigned char)titles[i][j]) == 'u')
                vowels++;
        }
        printf("%-5d %-30s %-10d %-10d\n", i + 1, titles[i], copies[i], vowels);
        if (copies[i] > copies[most_copies])
            most_copies = i;
    }

    printf("\nEnter a starting letter: ");
    scanf(" %c", &letter);
    letter = (char)tolower((unsigned char)letter);
    printf("Titles starting with %c:\n", letter);
    for (i = 0; i < 5; i++)
        if (tolower((unsigned char)titles[i][0]) == letter)
            printf("%s\n", titles[i]);

    printf("Title with the most copies: %s\n", titles[most_copies]);
    return 0;
}
