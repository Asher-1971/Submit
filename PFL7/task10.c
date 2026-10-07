#include <stdio.h>

int main(void)
{
    char username[21];
    int vowels = 0, consonants = 0, i;

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);

    for (i = 0; username[i] != '\0'; i++)
    {
        if (username[i] == '\n')
        {
            username[i] = '\0';
            break;
        }

        if ((username[i] >= 'A' && username[i] <= 'Z') ||
            (username[i] >= 'a' && username[i] <= 'z'))
        {
            char lowercase = username[i];

            if (lowercase >= 'A' && lowercase <= 'Z')
                lowercase += 'a' - 'A';

            if (lowercase == 'a' || lowercase == 'e' ||
                lowercase == 'i' || lowercase == 'o' ||
                lowercase == 'u')
                vowels++;
            else
                consonants++;

            if (username[i] >= 'a' && username[i] <= 'z')
                username[i] -= 'a' - 'A';
        }
    }

    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    printf("Uppercase username: %s\n", username);
    return 0;
}
