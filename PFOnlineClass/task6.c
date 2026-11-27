#include <stdio.h>

#define MAX_LENGTH 500

int main(void)
{
    char text[MAX_LENGTH];
    int length = 0;
    int left;
    int right;

    printf("Enter a line of text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        printf("Could not read the text.\n");
        return 1;
    }

    while (text[length] != '\0' && text[length] != '\n')
        length++;

    left = 0;
    right = length - 1;
    while (left < right)
    {
        char temporary = text[left];
        text[left] = text[right];
        text[right] = temporary;
        left++;
        right--;
    }
    text[length] = '\0';

    printf("Reversed string: %s\n", text);
    return 0;
}
