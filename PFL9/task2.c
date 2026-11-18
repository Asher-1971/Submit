#include <stdio.h>

void reverseDigits(long number)
{
    if (number < 10)
    {
        printf("%ld", number);
        return;
    }

    printf("%ld", number % 10);
    reverseDigits(number / 10);
}

int main(void)
{
    long number;

    printf("Enter a number: ");
    scanf("%ld", &number);

    if (number < 0)
        printf("Please enter a non-negative number.\n");
    else
    {
        printf("Reversed: ");
        reverseDigits(number);
        printf("\n");
    }

    return 0;
}
