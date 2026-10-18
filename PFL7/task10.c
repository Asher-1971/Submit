#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char username[21];
    int vowels = 0, consonants = 0, i;

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    for (i = 0; username[i] != '\0'; i++)
    {
        if (isalpha((unsigned char) username[i]))
        {
            if (tolower((unsigned char) username[i]) == 'a' ||
                tolower((unsigned char) username[i]) == 'e' ||
                tolower((unsigned char) username[i]) == 'i' ||
                tolower((unsigned char) username[i]) == 'o' ||
                tolower((unsigned char) username[i]) == 'u')
                vowels++;
            else
                consonants++;
        }

        username[i] = toupper((unsigned char) username[i]);
    }

    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    printf("Uppercase username: %s\n", username);
    return 0;
}
